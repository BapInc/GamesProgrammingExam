#ifndef NORMAL_DUNGEON
#define NORMAL_DUNGEON

#include "Dungeon.h"
#include "Room.h"
#include "../GameStates/LevelState.h"
class NormalDungeon : public Dungeon
{
public:
	NormalDungeon(LevelState& level);

protected:

	void generateRooms() override;
	void generateRoomConnections() override;
	void findVisibleRooms();
	void connectRooms();
	void generateRandomRoom();
	void generateRoomObject(RoomType type = RANDOMROOM, int customWidth = 0, int customHeight = 0);
	float CalculateDistance(glm::vec2& v, glm::vec2& w);

private:

	void swap(float& x, float& y);
	glm::ivec2 parseConnections(std::string& string);
	//TODO: Maybe keep pointers to start/end and reward rooms

	LevelState* levelState;

private:
	//TODO: Read these from a .json file

	std::vector<std::shared_ptr<Room>> rooms;
	std::vector<int> roomsConnected;

	float roomVisibilityDistance;

	int minDistanceBetweenRooms;
	int maxIterations; // NUmber of times it can iterate without creating a room, if higher then breaks out of the while loop

	int minRoomWidth;
	int maxRoomWidth;

	int minRoomHeight;
	int maxRoomHeight;

	int startRoomWidth;
	int startRoomHeight;

	int bossRoomWidth;
	int bossRoomHeight;

	char parserToken = '_';
};

#endif // ! NORMALDUNGEON
