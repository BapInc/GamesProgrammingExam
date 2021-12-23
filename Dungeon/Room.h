#ifndef ROOM_H
#define ROOM_H

#include "../Sprites/Tile.h"
#include <vector>

enum RoomType
{
	CUSTOMSIZE, RANDOMROOM, STARTROOM, BOSSROOM, REWARDSROOM
};

class Room
{
public:
	Room(int minWidth, int maxWidth, int minHeight, int MaxHeight);
	Room(int width, int height, RoomType type = CUSTOMSIZE);

	void SetTile(Tile tile ...);

	void generateContent();

public:

	int getWidth();
	int getHeight();

	RoomType getType();

private: 

	int width;
	int height;

	RoomType roomType;

	std::vector<Tile> floorTiles;
};
#endif