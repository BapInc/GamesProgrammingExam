#include "Room.h"
#include "../Utility/Debug.h"
#include <iostream>

int Room::amountOfRooms = 0;

Room::Room(int width, int height, glm::vec2 pos, glm::vec2 scale, RoomType type)
{
	this->width = width;
	this->height = height;

	initialPos = pos;
	//TODO: Make this 4 | 2 | 1 positions accordingly to the width and height. 
	centerPos = glm::vec2(pos.x + (width / 2), pos.y + (height / 2));
	centerPosScaled = glm::vec2((pos.x + (width / 2)) * scale.x, (pos.y + (height / 2)) * scale.y);

	roomType = type;

	roomNumber = amountOfRooms;
	amountOfRooms += 1;
}

glm::ivec2 Room::generateEnemy()
{
	//gets random position in the room
	int rands = rand() % tiles.size();
	glm::vec2 temp = tiles[rands] * scale;
	return temp;
}

void Room::addRoomSeen(std::shared_ptr<Room>& room, float& distance)
{
	//Should I really do this with the references?
	roomSeen.push_back(room); //Maybe this could be the room number instead
	roomSeenDistance.push_back(distance);
}

void Room::addRoomConnected(std::shared_ptr<Room>& room)
{
	roomsConnected.push_back(room);
}

void Room::sortRoomsSeen()
{
	bool swapped = false;
	for (size_t i = 0; i < roomSeenDistance.size(); i++)
	{
		swapped = false;
		for (size_t j = 0; j < roomSeenDistance.size() - 1; j++)
		{
			if (roomSeenDistance[j] > roomSeenDistance[j + 1])
			{
				swap(i, j);
				swapped = true;
			}
		}

		if (swapped == false)
			break;
	}
}

void Room::setTiles(std::vector<glm::vec2>& tilesContainer, glm::vec2 scale)
{
	tiles = tilesContainer;
	this->scale = scale;
}

void Room::swap(int i, int j)
{
	float temp = roomSeenDistance[i];
	auto tempRoom = roomSeen[i];

	roomSeen[i] = roomSeen[j];
	roomSeenDistance[i] = roomSeenDistance[j];

	roomSeen[j] = tempRoom;
	roomSeenDistance[j] = temp;
}

int Room::getWidth()
{
	return width;
}

int Room::getHeight()
{
	return height;
}

glm::ivec2 Room::getCenterPos() const
{
	return centerPos;
}

glm::ivec2 Room::getCenterPosScaled() const
{
	return centerPosScaled;
}

std::vector<std::shared_ptr<Room>> Room::getRoomsSeen()
{
	return roomSeen;
}

std::vector<std::shared_ptr<Room>> Room::getRoomsConnected()
{
	return roomsConnected;
}

float Room::getRoomSeenDistance(int i)
{
	return roomSeenDistance[i];
}

RoomType Room::getType()
{
	return roomType;
}
int Room::getRoomNumber() const
{
	return roomNumber;
}
//
//const int Room::getRoomNumber() const
//{
//	return roomNumber;
//}
