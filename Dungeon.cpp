#include "Dungeon.h"
#include "Debug.h"

void Dungeon::generateDungeon()
{
	setMapValues();
	calculateAmountOfRooms();
	generateRooms();
}

void Dungeon::setMapValues()
{
	std::vector<int> emptyVector;
	dungeonMap.push_back(emptyVector);
	dungeonMap.push_back(emptyVector);

	for (size_t i = 0; i < mapWidth; i++)
	{
		for (size_t j = 0; j < mapHeight; j++)
		{
			dungeonMap[i][j] = 0;
		}
	}
}

void Dungeon::calculateAmountOfRooms()
{
	amountOfRooms = rand() % maxAmountOfRooms + minAmountOfRooms;
	Debug::Log("Amount of rooms " + std::to_string(amountOfRooms));
}
