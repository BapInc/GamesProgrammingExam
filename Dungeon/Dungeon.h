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
	virtual void generateContent() {};
	
public:

	void drawAsciiDungeon();

protected:

	std::vector<std::vector<GameObject *>> dungeonMap;

protected:
	std::shared_ptr<Room> startRoom;
	int mapWidth;
	int mapHeight;

	int minAmountOfRooms;
	int maxAmountOfRooms;
	int amountOfRooms;
};
#endif
