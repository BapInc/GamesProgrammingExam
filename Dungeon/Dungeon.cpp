#include "Dungeon.h"
#include "../Utility/Debug.h"
#include <iostream>

void Dungeon::generateDungeon()
{
	setMapValues();
	calculateAmountOfRooms();
	generateRooms();
}

void Dungeon::setMapValues()
{
	for (size_t i = 0; i < mapWidth; i++)
		dungeonMap.push_back(std::vector<GameObject *>(mapHeight));	
}

void Dungeon::calculateAmountOfRooms()
{
	srand(time(NULL));
	amountOfRooms = rand() % (maxAmountOfRooms - minAmountOfRooms + 1) + minAmountOfRooms;
	Debug::Log("Amount of rooms " + std::to_string(amountOfRooms));
}
