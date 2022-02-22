#include "NormalDungeon.h"
#include "../Utility/Debug.h"
#include "../Components/SpriteComponent.h"
#include "../Managers/PrefabManager.h"
#include <algorithm>
#include <iostream>
#include <cmath>
#include <map>
#include <string>

typedef  std::pair<int, int> iPair;

NormalDungeon::NormalDungeon(LevelState& levelState)
{
	minAmountOfRooms = 5;
	maxAmountOfRooms = 10;

	minRoomWidth = 10;
	minRoomHeight = 10;
	maxRoomHeight = 14;
	maxRoomWidth = 14;

	startRoomWidth = 5;
	startRoomHeight = 5;

	mapWidth = 100;
	mapHeight = 100;

	scaleMultiplier = 4.0f;

	amountOfFloorPrefabs = 8;
	amountOfWallPrefabs = 3;

	minAmountOfEnemies = 1;
	maxAmountOfEnemies = 3;

	if (minRoomHeight > maxRoomHeight)
		Debug::Log("Min Room Height is bigger than Max Room height", WARNING);

	if (minRoomWidth > maxRoomWidth)
		Debug::Log("Min Room Width is bigger than Max Room Width", WARNING);

	roomVisibilityDistance = 100;

	maxIterations = 100;

	minDistanceBetweenRooms = 3;

	this->levelState = &levelState;

	auto sprit = this->levelState->getSprite("floor_1.png");
	tileSize = sprit.getSpriteSize();
}

void NormalDungeon::generateRooms()
{
	//Generate starting room
	do
	{
		generateRoom(startRoomWidth, startRoomHeight, STARTROOM);

	} while (rooms.size() == 0);

	//Get random position
	int temp = 0;

	//50 being the percentage of how much the rooms can fill (Not counting walls nor corridors) 
	maxRoomFill = 50.0f;
	int maxTiles = (mapHeight * maxRoomHeight) / maxRoomFill; 

	int isWithoutRoom = 0;

	//Max Room tiles and counting walls (Not corridors)
	int maxPossibleTiles = maxRoomHeight * maxRoomWidth * maxAmountOfRooms + ((maxRoomWidth * 2) + (maxRoomHeight * 2) + 4) * maxAmountOfRooms;
	int mapTilesCount = mapWidth * mapHeight;
	Debug::Log("MAX Tiles: " + std::to_string(maxPossibleTiles) + " | Map Tiles: " + std::to_string(mapTilesCount));

	if (maxPossibleTiles >= mapTilesCount)
		Debug::Log("ROOM TILES ARE BIGGER THAN MAP", ALERT);

	do
	{
		//Check if empty, if not empty go back
		int width = rand() % (maxRoomWidth - minRoomWidth + 1) + minRoomWidth;
		int height = rand() % (maxRoomHeight - minRoomHeight + 1) + minRoomHeight;

		//Rand safety checks
		if (minRoomWidth == maxRoomWidth)
			width = minRoomWidth;

		if (minRoomHeight == maxRoomHeight)
			height = minRoomHeight;

		if (!generateRoom(width, height))
			isWithoutRoom += 1;

		if (isWithoutRoom > maxIterations)
		{
			Debug::Log("Map Size is too small, not all rooms generated", ALERT);
			break;
		}

	} while (rooms.size() != amountOfRooms);
}

bool NormalDungeon::generateRoom(int& width, int& height, RoomType type)
{
	bool breakout = false;

	//Random Point in map
	int randX = rand() % mapWidth;
	int randY = rand() % mapHeight;

	int minOutOfBounds = 1;

	//If out of bounds reset || This can be replaced so randX and randY are smaller than mapWidth or height also needs a difference so it's not too close to borders for walls
	if (randX + width > mapWidth || randY + height > mapHeight)
	{
		return false;
	}

	for (int i = -minDistanceBetweenRooms; i < width + minDistanceBetweenRooms; i++)
	{
		for (int j = -minDistanceBetweenRooms; j < height + minDistanceBetweenRooms; j++)
		{
			//If out of bounds go to next iteration
			if (i + randX < minOutOfBounds
				|| j + randY < minOutOfBounds
				|| i + randX >= mapWidth - minOutOfBounds
				|| j + randY >= mapHeight - minOutOfBounds)
			{
				breakout = true;
				break;
			}

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
		return false;
	}

	//For Loops are done again, just so there's no need to create and destroy objects in memory
	//Loops width and height and adds floor tiles and its attributes
	std::vector<glm::vec2> tempVector;
	for (size_t i = 0; i < width; i++)
	{
		for (size_t j = 0; j < height; j++)
		{
			createFloor(randX + i, randY + j);
			tempVector.push_back(glm::vec2(randX + i, randY + j));
			
		}
	}

	//Rooom created successfully
	auto room = std::shared_ptr<Room>(new Room(width, height, glm::vec2(randX, randY), tileSize * scaleMultiplier, type));
	rooms.push_back(room);
	room->setTiles(tempVector, tileSize * scaleMultiplier);

	switch (type)
	{
	case RANDOMROOM:

		break;
	case STARTROOM:

		if (startRoom != NULL)
			Debug::Log("More than one startRoom instance", ALERT);
		else
			startRoom = room;

		break;
	case BOSSROOM:

		break;
	case REWARDSROOM:

		break;
	default:
		break;
	}
}

void NormalDungeon::generateRoomConnections()
{
	findVisibleRooms();

	connectRooms();
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
	std::vector<float> keys;
	std::map<float, std::string> costs;
	int selectedRoom = 0;
	bool isFirstConnection = true;
	while (roomsConnected.size() != rooms.size())
	{
		for (size_t j = 0; j < rooms[selectedRoom]->getRoomsSeen().size(); j++)
		{
			//Add all seen costs to list
			int roomSeen = rooms[selectedRoom]->getRoomsSeen()[j]->getRoomNumber();

			//If room is not in cycle add cost
			if (std::find(roomsConnected.begin(), roomsConnected.end(), roomSeen) == roomsConnected.end())
			{
				std::string temp = std::to_string(rooms[selectedRoom]->getRoomNumber()) + parserToken + std::to_string(roomSeen);
				float distance = rooms[selectedRoom]->getRoomSeenDistance(j);

				float tempDistanceAdditive = 0.000002f;
				bool loop = true;
				//if same distance is already in map
				if (costs.find(distance) != costs.end())
				{
					while (loop)
					{
						distance += tempDistanceAdditive;
						if (costs.find(distance) == costs.end())
							loop = false;
					}
				}

				costs[distance] = temp;
				keys.push_back(distance);
			}
		}

		sortCosts(keys);

		glm::ivec2 connectRooms;

		bool isRoomInCycle = false;
		do
		{
			connectRooms = parseConnections(costs[keys[0]]);
			if (std::find(roomsConnected.begin(), roomsConnected.end(), connectRooms.y) != roomsConnected.end())
			{
				costs.erase(keys[0]);
				keys.erase(keys.begin());
				isRoomInCycle = true;
			}
			else
			{
				isRoomInCycle = false;
			}

		} while (isRoomInCycle == true);

		float distance = keys[0];

		//Add connections to both rooms
		if (isFirstConnection)
		{
			roomsConnected.push_back(connectRooms.x);
			isFirstConnection = false;
		}

		//Add rooms to the cycle
		roomsConnected.push_back(connectRooms.y);
		selectedRoom = connectRooms.y;
		//Remove room from costs
		costs.erase(distance);
		keys.erase(keys.begin());

		//room connections
		rooms[connectRooms.x]->addRoomConnected(rooms[connectRooms.y]);
		rooms[connectRooms.y]->addRoomConnected(rooms[connectRooms.x]);
		//Generate corridor and connect rooms

		generateCorridor(connectRooms.x, connectRooms.y);
	}
}

//Generate each corridor connection between two rooms
void NormalDungeon::generateCorridor(int roomOne, int roomTwo)
{
	//Randomize if it starts on y or x. 
	int randomDir = rand() % 2;

	//for loop for each axis
	int secondDir;
	glm::ivec2 tempDistance;
	tempDistance.x = rooms[roomOne]->getCenterPos().x - rooms[roomTwo]->getCenterPos().x;
	tempDistance.y = rooms[roomOne]->getCenterPos().y - rooms[roomTwo]->getCenterPos().y;

	generateCorridorAxis(true, randomDir, roomOne, roomTwo, tempDistance, rooms[roomOne]->getCenterPos());
}

//Generate corridors on both axis
void NormalDungeon::generateCorridorAxis(bool first, int axis, int roomOne, int roomTwo, glm::ivec2& distance, glm::ivec2 startPos)
{
	int tileDistance = 0;
	int additive = -1;
	if (axis == 0)
	{
		axis++;
		tileDistance = std::abs(distance.x);
		if (distance.x < 0)
			additive = 1;
	}
	else
	{
		axis--;
		tileDistance = std::abs(distance.y);
	}

	glm::ivec2 pos = startPos;
	for (size_t i = 0; i < tileDistance; i++)
	{
		additive = 1;
		if (axis == 1)
		{
			if (distance.x > 0)
				additive = -1;

			pos = glm::ivec2(pos.x + additive, pos.y);
			createFloor(pos.x, pos.y);
		}
		else
		{
			if (distance.y > 0)
				additive = -1;

			pos = glm::ivec2(pos.x, pos.y + additive);
			createFloor(pos.x, pos.y);
		}
	}

	if (first)
		generateCorridorAxis(false, axis, roomOne, roomTwo, distance, pos);
}

//Generate walls surrounnding the floorTiles
void NormalDungeon::generateWalls()
{
	for (size_t i = 0; i < mapHeight; i++)
	{
		for (size_t j = 0; j < mapWidth; j++)
		{
			if (dungeonMap[j][i] == NULL)
				continue;

			if (dungeonMap[j][i]->getName() != "floorTile")
				continue;

			//Rows
			for (int r = -1; r < 2; r++)
			{
				//Columns
				for (int c = -1; c < 2; c++)
				{
					if (r == 0 && c == 0)
						continue;

					if (j + r >= mapWidth || i + c >= mapHeight)
						continue;

					if (j + r < 0 || i + c < 0)
						continue;

					if (dungeonMap[j + r][i + c] == NULL)
						createWall(j + r, i + c);
				}
			}
		}
	}
}

void NormalDungeon::generateContent()
{
	generateEnemies();
}

//Gennerate enemies for each random room
void NormalDungeon::generateEnemies()
{
	for (size_t i = 0; i < rooms.size(); i++)
	{
		if (rooms[i]->getType() != RANDOMROOM)
			continue;

		int temp = rand() % (maxAmountOfEnemies - minAmountOfEnemies + 1) + minAmountOfEnemies;
		
		for (size_t j = 0; j < temp; j++)
		{
			glm::ivec2 tempPos = rooms[i]->generateEnemy();
			
			
			levelState->generateEnemy(tempPos);
		}
	}
}

void NormalDungeon::createFloor(int x, int y)
{
	if (dungeonMap[x][y] != nullptr)
		return;

	std::string spriteName = "floorTile";
	int random = rand() % amountOfFloorPrefabs;
	random += 1;

	std::shared_ptr<GameObject> temp = levelState->loadPrefab(spriteName + std::to_string(random), glm::vec2(0, 0));
	temp->setName(spriteName);

	dungeonMap[x][y] = temp.get();
	dungeonMap[x][y]->getTransform()->SetPos(glm::vec2((x) * (tileSize.x * scaleMultiplier),
		(y) * (tileSize.y * scaleMultiplier)));
}

void NormalDungeon::createWall(int x, int y)
{
	if (dungeonMap[x][y] != nullptr)
		return;

	std::string spriteName = "wallTile";
	int random = rand() % amountOfWallPrefabs;
	random += 1;

	std::shared_ptr<GameObject> temp = levelState->loadPrefab(spriteName + std::to_string(random), glm::vec2(0, 0));
	temp->setName(spriteName);
	dungeonMap[x][y] = temp.get();
	dungeonMap[x][y]->getTransform()->SetPos(glm::vec2((x) * (tileSize.x * scaleMultiplier),
		(y) * (tileSize.y * scaleMultiplier)));

	auto pC = temp.get()->addComponent<PhysicsComponent>();
	pC->setWorld(levelState->getPhysicsWorld());
	pC->initBox(b2_staticBody, glm::vec2(0.3f, 0.3f), temp->getTransform()->getPos(), 1.0f);
	levelState->addPhysicsComponent(pC);
}

float NormalDungeon::CalculateDistance(glm::ivec2& v, glm::ivec2& w)
{
	return abs(sqrt(pow(v.x - w.x, 2) + pow(v.y - w.y, 2)));
}

void NormalDungeon::swap(float& x, float& y)
{
	float temp = x;
	x = y;
	y = temp;
}

void NormalDungeon::sortCosts(std::vector<float>& mapkeys)
{
	bool swapped = false;
	for (size_t i = 0; i < mapkeys.size(); i++)
	{
		swapped = false;
		for (size_t j = 0; j < mapkeys.size() - 1; j++)
		{
			if (mapkeys[j] > mapkeys[j + 1])
			{
				swap(mapkeys[j], mapkeys[j + 1]);
				swapped = true;
			}
		}

		if (swapped == false)
			break;
	}
}

glm::ivec2 NormalDungeon::parseConnections(std::string& string)
{
	glm::ivec2 temp;
	std::string tempString;
	int pos = string.find(parserToken);

	tempString = string.substr(0, pos);
	std::string tempString2 = string.substr(pos + 1, std::string::npos);

	temp.x = std::stoi(tempString);
	temp.y = std::stoi(tempString2);
	return temp;
}
