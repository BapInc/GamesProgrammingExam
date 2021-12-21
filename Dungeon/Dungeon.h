#ifndef DUNGEON
#define DUNGEOn

#include <vector>

class Dungeon
{
public:
	virtual void generateDungeon();

protected:
	void setMapValues();
	void calculateAmountOfRooms();
	virtual void generateRooms() {};
	
	std::vector<std::vector<int>> dungeonMap;

protected:

	int mapWidth;
	int mapHeight;

	int minAmountOfRooms;
	int maxAmountOfRooms;
	int amountOfRooms;
};
#endif
