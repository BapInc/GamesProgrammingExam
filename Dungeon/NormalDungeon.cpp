#include "NormalDungeon.h"
#include "../Utility/Debug.h"
#include "../Components/SpriteComponent.h"
#include <iostream>

NormalDungeon::NormalDungeon(LevelState& levelState)
{
	minAmountOfRooms = 3;
	maxAmountOfRooms = 5;

	minRoomWidth = 3;
	minRoomHeight = 3;
	maxRoomHeight = 5;
	maxRoomWidth = 5;

	mapWidth = 30;
	mapHeight = 30;

	minDistanceBetweenRooms = 3;

	this->levelState = &levelState;
}

void NormalDungeon::generateRooms()
{
	//Get random position
	int temp = 0;

	//TODO: Stop hardcoding the value 50
	int maxTiles = (mapHeight * maxRoomHeight) / 50; //50 being the percentage of how much the rooms can fill (Not counting walls nor corridors) 


	int numberOfTiles = 0;

	do
	{
		//Random Point in map
		int randX = rand() % mapWidth;
		int randY = rand() % mapHeight;

		//Debug::Log("MAP XPOS: " + std::to_string(randX) + "| Map YPOS: " + std::to_string(randY));

		//Check if empty, if not empty go back
		int width = rand() % maxRoomWidth + minRoomWidth;
		int height = rand() % maxRoomHeight + minRoomHeight;

		//If out of bounds reset || This can be replaced so randX and randY are smaller than mapWidth or height also needs a difference so it's not too close to borders for walls
		if (randX + width > mapWidth || randY + height > mapHeight)
		{
			continue;
		}

		bool breakout = false;
		for (int i = -minDistanceBetweenRooms; i < width + minDistanceBetweenRooms ; i++)
		{
			for (int j = -minDistanceBetweenRooms; j < height + minDistanceBetweenRooms ; j++)
			{
				if (   i + randX < 0 
					|| j + randY < 0
					|| i + randX >= mapWidth 
					|| j + randY >= mapHeight)
					continue;
				//TODO: Tiles created for a specific room should get deleted if another tile is found
				if (dungeonMap[randX + i][randY + j] != nullptr)
				{
					breakout = true;
					break;
				}
			}

			if (breakout)
				break;
		}

		if (breakout)
			continue;

		//For Loops are done again, just so there's no need to create and destroy object in memory
		for (size_t i = 0; i < width; i++)
		{
			for (size_t j = 0; j < height; j++)
			{
				auto obj = new GameObject();
				std::string name = "floorTile";
				obj->setName(name);
				auto spC = obj->addComponent<SpriteComponent>();
				auto sprit = levelState->getSprite("floor_1.png"); // spriteAtlas->get("floor_1.png");
				float scaleMultiplier = 2.0f;
				sprit.setScale({ scaleMultiplier,scaleMultiplier });
				spC->setSprite(sprit);

				dungeonMap[randX + i][randY + j] = obj;
				dungeonMap[randX + i][randY + j]->getTransform()->SetPos(glm::vec2((randX + i) * (sprit.getSpriteSize().x * scaleMultiplier), (randY + j) * (sprit.getSpriteSize().y * scaleMultiplier)));
				levelState->createGameObject(dungeonMap[randX + i][randY + j]);
			}
		}

		

		numberOfTiles += width * height;
		//If room is generated succesfully
		temp += 1;
	} while (temp != amountOfRooms);

	for (size_t i = 0; i < mapHeight; i++)
	{
		for (size_t j = 0; j < mapWidth; j++)
		{
			auto temp = dungeonMap[j][i];
			char tempChar = ' ';

			if (temp != nullptr)
				tempChar = '.';

			std::cout << tempChar;
		}
		std::cout << std::endl;
	}
}


void NormalDungeon::generateRandomRoom()
{
	int width = rand() % (maxRoomWidth - minRoomWidth + 1) - minRoomWidth;
	int height = rand() % (maxRoomHeight - minRoomHeight + 1) - minRoomHeight;
}
void NormalDungeon::generateRoomObject(RoomType type, int customWidth, int customHeight)
{
	Room* room;
	switch (type)
	{
	case CUSTOMSIZE:

		room = new Room(customWidth, customHeight);

		break;
	case RANDOMROOM:

		room = new Room(minRoomWidth, maxRoomWidth, minRoomHeight, maxRoomHeight);

		break;
	case STARTROOM:

		room = new Room(startRoomWidth, startRoomHeight, STARTROOM);

		break;
	case BOSSROOM:

		room = new Room(bossRoomWidth, bossRoomHeight, BOSSROOM);

		break;
	case REWARDSROOM:

		//TODO: Improve rewards room customisation
		room = new Room(customWidth, customHeight, REWARDSROOM);
		break;
	default:
		break;
	}
}
