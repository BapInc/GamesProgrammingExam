#include "Room.h"
#include "../Utility/Debug.h"


Room::Room(int minWidth, int maxWidth, int minHeight, int maxHeight)
{
	width = rand() % (maxWidth - minWidth + 1) - minWidth;
	height = rand() %(maxHeight - minHeight + 1) - minHeight;

	roomType = RANDOMROOM;
}

Room::Room(int width, int height, RoomType type)
{
	this->width = width;
	this->height = height;

	roomType = type;
}

void Room::SetTile(Tile tile...)
{

	floorTiles.push_back(tile);
	Debug::Log("FLOOR TILES SIZE " + std::to_string(floorTiles.size()));
}

void Room::generateContent()
{
}

int Room::getWidth()
{
	return width;
}

int Room::getHeight()
{
	return height;
}

RoomType Room::getType()
{
	return roomType;
}
