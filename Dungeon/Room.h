#ifndef ROOM_H
#define ROOM_H

#include "../Sprites/Tile.h"
#include <vector>
#include <map>

enum RoomType
{
	CUSTOMSIZE, RANDOMROOM, STARTROOM, BOSSROOM, REWARDSROOM
};

class Room
{
public:
	Room(int width, int height, glm::vec2 pos, RoomType type = CUSTOMSIZE);

	void initialiseRoom();
	void generateContent();

public:

	void addRoomSeen(std::shared_ptr<Room>& room, float& distance);
	void sortRoomsSeen();

public:

	int getWidth();
	int getHeight();
	glm::vec2 getCenterPos() const;
	std::vector <std::shared_ptr<Room>> getRoomsSeen();

	RoomType getType();
	

private: 

	int width;
	int height;
	glm::vec2 initialPos;
	glm::vec2 centerPos;

	std::vector <std::shared_ptr<Room>> roomSeen;
	std::vector <float> roomSeenDistance;
	std::vector <std::shared_ptr<int>> roomsConnected;

	std::vector<std::shared_ptr<char>> roomMap;
	//TODO: Maybe use if sort isn't used and to shift objects around
	std::vector<std::shared_ptr<Room>> closestRooms;
	RoomType roomType;
};
#endif