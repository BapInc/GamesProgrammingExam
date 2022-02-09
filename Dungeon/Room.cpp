#include "Room.h"
#include "../Utility/Debug.h"
#include <iostream>

Room::Room(int width, int height, glm::vec2 pos, RoomType type)
{
	this->width = width;
	this->height = height;

	initialPos = pos;
	this->centerPos = glm::vec2(pos.x + (width / 2), pos.y + (height / 2));
	roomType = type;
}

void Room::initialiseRoom()
{
}

void Room::generateContent()
{
}

void Room::addRoomSeen(std::shared_ptr<Room>& room, float& distance)
{
	//Should I really do this with the references?
	roomSeen.push_back(room); //Maybe this could be the room number instead
	roomSeenDistance.push_back(distance);
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
				Swap(roomSeenDistance[j], roomSeenDistance[j + 1]);
				swapped = true;
			}
		}

		if (swapped == false)
			break;
	}
}

void Room::Swap(float& x, float& y)
{
	float temp = x;
	x = y;
	y = temp;
}

int Room::getWidth()
{
	return width;
}

int Room::getHeight()
{
	return height;
}

glm::vec2 Room::getCenterPos() const
{
	return centerPos;
}

std::vector<std::shared_ptr<Room>> Room::getRoomsSeen()
{
	return roomSeen;
}

RoomType Room::getType()
{
	return roomType;
}
