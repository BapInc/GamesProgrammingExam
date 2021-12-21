#include "NormalDungeon.h"

NormalDungeon::NormalDungeon()
{
	minAmountOfRooms = 5;
	maxAmountOfRooms = 10;
}

void NormalDungeon::generateRooms()
{
	int temp = 0;
	while (temp != amountOfRooms);
	{


		for (size_t i = 0; i < mapWidth; i++)
		{
			for (size_t i = 0; i < mapHeight; i++)
			{
				//If room is generated succesfully
				temp += 1;
			}
		}
	}
}
