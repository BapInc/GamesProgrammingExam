#include "NormalDungeon.h"
#include "../Utility/Debug.h"
#include "../Components/SpriteComponent.h"
#include "../Game/SpriteManager.h"

NormalDungeon::NormalDungeon(LevelState& levelState)
{
	minAmountOfRooms = 1;
	maxAmountOfRooms = 1;

	minRoomWidth = 3;
	minRoomHeight = 3;
	maxRoomHeight = 5;
	maxRoomWidth = 5;

	mapWidth = 30;
	mapHeight = 30;

	this->levelState = &levelState;
}

void NormalDungeon::generateRooms()
{
	//Get random position
	int temp = 0;

	//TODO: Stop hardcoding the value 50
	int maxTiles = (mapHeight * maxRoomHeight) / 50; //50 being the percentage of how much the rooms can fill (Not counting walls nor corridors) 




	do
	{
		//Random Point in map
		int randX = rand() % mapWidth;
		int randY = rand() % mapHeight;

		Debug::Log("MAP XPOS: " + std::to_string(randX) + "| Map YPOS: " + std::to_string(randY));

		//Check if empty, if not empty go back
		int width = rand() % maxRoomWidth + minRoomWidth;
		int height = rand() % maxRoomHeight + minRoomHeight;

		//If out of bounds reset || This can be replaced so randX and randY are smaller than mapWidth or height also needs a difference so it's not too close to borders for walls
		if (randX + width > mapWidth || randY + height > mapHeight)
			continue;

		for (size_t i = 0; i < width; i++)
		{
			for (size_t j = 0; j < height; j++)
			{
				//TODO: Tiles created for a specific room should get deleted if another tile is found
				if (dungeonMap[randX + i][randY + j] != nullptr)
					continue;
			}
		}

		//For Loops are done again, just so there's no need to create and destroy object in memory
		for (size_t i = 0; i < width; i++)
		{
			for (size_t j = 0; j < height; j++)
			{
				auto obj = new GameObject();
				obj->name = "floorTile";
				auto spC = obj->addComponent<SpriteComponent>();
				auto sprit = SpriteManager::getInstance()->getSprite("floor_1.png"); // spriteAtlas->get("floor_1.png");
				//sprit->setScale({ 2,2 });
				spC->setSprite(*sprit);

				dungeonMap[randX + i][randY + j] = obj;
				dungeonMap[randX + i][randY + j]->setPosition(glm::vec2((randX + i) * sprit->getSpriteSize().x, (randY + j) * sprit->getSpriteSize().y));
				levelState->createGameObject(dungeonMap[randX + i][randY + j]);
			}
		}

		//If room is generated succesfully
		temp += 1;

		Debug::Log("ROOM CREATED");

		//for (size_t i = 0; i < mapWidth; i++)
		//{
		//	for (size_t i = 0; i < mapHeight; i++)
		//	{

		//	}
		//}
	} while (temp != amountOfRooms);
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
