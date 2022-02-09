#include "Dungeon.h"
#include "../Utility/Debug.h"
#include <iostream>

void Dungeon::generateDungeon()
{
	setMapValues();
	calculateAmountOfRooms();
	generateRooms();
	generateRoomConnections();
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

void Dungeon::drawAsciiDungeon()
{
	//TODO: Diferentiate walls, floor, enemies and other content
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
