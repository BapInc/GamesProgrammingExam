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
	void generateRandomRoom();
	void generateRoomObject(RoomType type = RANDOMROOM, int customWidth = 0, int customHeight = 0);


private:

	//TODO: Maybe keep pointers to start/end and reward rooms

	LevelState* levelState;

private:
	//TODO: Read these from a .json file

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
};

#endif // ! NORMALDUNGEON
