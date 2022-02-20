#ifndef ROOM_H
#define ROOM_H

#include "../Sprites/Tile.h"
#include <vector>
#include <map>

enum RoomType
{
	RANDOMROOM, STARTROOM, BOSSROOM, REWARDSROOM
};

class Room
{
public:
	Room(int width, int height, glm::vec2 pos, glm::vec2 scale, RoomType type = RANDOMROOM);

	void initialiseRoom();
	void generateContent();

public:

	void addRoomSeen(std::shared_ptr<Room>& room, float& distance);
	void addRoomConnected(std::shared_ptr<Room>& room);
	void sortRoomsSeen();
private:
	void swap(int i, int j);
public:

	int getWidth();
	int getHeight();
	glm::ivec2 getCenterPos() const;
	glm::ivec2 getCenterPosScaled() const;
	std::vector <std::shared_ptr<Room>> getRoomsSeen();
	std::vector <std::shared_ptr<Room>> getRoomsConnected();
	float getRoomSeenDistance(int i);
	RoomType getType();
	int getRoomNumber() const;
	
private: 

	int width;
	int height;
	int roomNumber;
	static int amountOfRooms;
	glm::vec2 initialPos;
	glm::ivec2 centerPos;
	glm::ivec2 centerPosScaled;

	std::vector <std::shared_ptr<Room>> roomSeen;
	std::vector <float> roomSeenDistance;
	std::vector <std::shared_ptr<Room>> roomsConnected;

	std::vector<std::shared_ptr<char>> roomMap;
	//TODO: Maybe use if sort isn't used and to shift objects around
	std::vector<std::shared_ptr<Room>> closestRooms;
	RoomType roomType;
};
#endif