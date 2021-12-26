#ifndef DUNGEON
#define DUNGEOn

#include <vector>
#include "../Game/GameObject.h"
#include <sre/Sprite.hpp>

class Dungeon
{
public:
	virtual void generateDungeon();

protected:
	void setMapValues();
	void calculateAmountOfRooms();
	virtual void generateRooms() {};
	
public:

public:

	void drawAsciiDungeon();

	//TODO: Should this be with sharedpointers instead of normal pointers?
	std::vector<std::vector<GameObject *>> dungeonMap;

	std::vector<sre::Sprite* > floorSprites;

protected:

	int mapWidth;
	int mapHeight;

	int minAmountOfRooms;
	int maxAmountOfRooms;
	int amountOfRooms;
};
#endif
