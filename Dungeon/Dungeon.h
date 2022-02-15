#ifndef DUNGEON
#define DUNGEOn

#include <vector>
#include "Room.h"
#include "../Game/GameObject.h"
#include <sre/Sprite.hpp>

class Dungeon
{
public:
	virtual void generateDungeon();

public:

	glm::ivec2 getStartRoomPos();

protected:

	void setMapValues();
	void calculateAmountOfRooms();

	virtual void generateRooms() {};
	virtual void generateRoomConnections() {};
	virtual void generateWalls() {};
	
public:

	void drawAsciiDungeon();

protected:

	//TODO: Should this be with sharedpointers instead of normal pointers?
	std::vector<std::vector<GameObject *>> dungeonMap;

	std::vector<sre::Sprite* > floorSprites;

protected:
	std::shared_ptr<Room> startRoom;
	int mapWidth;
	int mapHeight;

	int minAmountOfRooms;
	int maxAmountOfRooms;
	int amountOfRooms;
};
#endif
