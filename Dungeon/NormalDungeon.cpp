#include "NormalDungeon.h"
#include "../Utility/Debug.h"
#include "../Components/SpriteComponent.h"
#include <iostream>
#include <cmath>

typedef  std::pair<int, int> iPair;

NormalDungeon::NormalDungeon(LevelState& levelState)
{
	minAmountOfRooms = 3;
	maxAmountOfRooms = 5;

	minRoomWidth = 3;
	minRoomHeight = 3;
	maxRoomHeight = 5;
	maxRoomWidth = 5;

	roomVisibilityDistance = 100;

	mapWidth = 30;
	mapHeight = 30;

	maxIterations = 100;

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
	int itWithoutRoom = 0;

	//TODO: Check if max possible tiles calculation is working currectly when walls are being generated
	//Max Room tiles and counting walls (Not corridors)
	int maxPossibleTiles = maxRoomHeight * maxRoomWidth * maxAmountOfRooms + ((maxRoomWidth * 2 ) + (maxRoomHeight * 2) + 4) * maxAmountOfRooms;
	int mapTilesCount = mapWidth * mapHeight;
	Debug::Log("MAX Tiles: " + std::to_string(maxPossibleTiles) + " | Map Tiles: " + std::to_string(mapTilesCount));

	if (maxPossibleTiles >= mapTilesCount)
		Debug::Log("ROOM TILES ARE BIGGER THAN MAP", ALERT);

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
				//IF OUT OF BOUNDS CONTINUE
				if (   i + randX < 0 
					|| j + randY < 0
					|| i + randX >= mapWidth 
					|| j + randY >= mapHeight)
					continue;
				
				//If there's already a tile in the calculated area, reset while loop
				if (dungeonMap[randX + i][randY + j] != nullptr)
				{
					breakout = true;
					break;
				}
			}

			if (breakout)
				break;
		}

		//Reset While loop
		if (breakout)
		{
			itWithoutRoom += 1;

			if (itWithoutRoom > maxIterations)
			{
				Debug::Log("Map Size is too small, not all rooms generated", ALERT);
				break;
			}

			continue;
		}

		//For Loops are done again, just so there's no need to create and destroy object in memory
		//Loops width and height and adds floor tiles and its attributes
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
				itWithoutRoom = 0;
			}
		}

		//If room is generated succesfully
		auto room = std::shared_ptr<Room>(new Room(width, height,glm::vec2(randX, randY), RANDOMROOM));
		rooms.push_back(room);
		numberOfTiles += width * height;

		temp += 1;

	} while (rooms.size() != amountOfRooms);
}

void NormalDungeon::generateRoomConnections()
{
	//check 

	//Calculate all room distances
	findVisibleRooms();
}

void NormalDungeon::findVisibleRooms()
{
	//Create Vector organised with lowest to highest costs
	//This needs to then know which rooms it is trying to acess, maybe use strings for this
	float tempDistance;
	int i, j = 0;

	for (size_t i = 0; i < rooms.size(); i++)
	{
		for (size_t j = 0; j < rooms.size(); j++)
		{
			//skip if it's the same room
			if (i == j)
				continue;

			//Add reference to Vector of rooms in each one and calculate distance between them
			tempDistance = CalculateDistance(rooms[i]->getCenterPos(), rooms[j]->getCenterPos());

			if (tempDistance > roomVisibilityDistance)
				continue;

			rooms[i]->addRoomSeen(rooms[j], tempDistance);
		}

		//sort vector of rooms depending on distances
		rooms[i]->sortRoomsSeen();
	}
}

void NormalDungeon::connectRooms()
{
	std::vector<std::string> cost;
	int selectedRoom = 0;
	while (roomsConnected.size() != rooms.size())
	{
		for (size_t i = 0; i < rooms[selectedRoom]->getRoomsSeen().size(); i++)
		{
			//Add all seen costs to list
			//std::string temp = 
			//cost.push_back()
		}

		//TODO: Chose the cheapest cost and do it, no need to check if there are equal costs.

		//Generate corridor and connect rooms
	}
}

void NormalDungeon::generateRandomRoom()
{
	int width = rand() % (maxRoomWidth - minRoomWidth + 1) - minRoomWidth;
	int height = rand() % (maxRoomHeight - minRoomHeight + 1) - minRoomHeight;
}
void NormalDungeon::generateRoomObject(RoomType type, int customWidth, int customHeight)
{
	//Room* room;
	//switch (type)
	//{
	//case CUSTOMSIZE:

	//	room = new Room(customWidth, customHeight);

	//	break;
	//case RANDOMROOM:

	//	room = new Room(minRoomWidth, maxRoomWidth, minRoomHeight, maxRoomHeight);

	//	break;
	//case STARTROOM:

	//	room = new Room(startRoomWidth, startRoomHeight, STARTROOM);

	//	break;
	//case BOSSROOM:

	//	room = new Room(bossRoomWidth, bossRoomHeight, BOSSROOM);

	//	break;
	//case REWARDSROOM:

	//	//TODO: Improve rewards room customisation
	//	room = new Room(customWidth, customHeight, REWARDSROOM);
	//	break;
	//default:
	//	break;
	//}
}

float NormalDungeon::CalculateDistance(glm::vec2& v, glm::vec2& w)
{
	return abs(sqrt(pow(v.x - w.x, 2) + pow(v.y - w.y, 2)));	
}

void NormalDungeon::BubbleSort()
{
}
