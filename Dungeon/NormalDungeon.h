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
	bool generateRoom(int& width, int& height, RoomType type = RANDOMROOM);
	void generateRoomConnections() override;
	void findVisibleRooms();
	void createFloor(int x, int y);
	void createWall(int x, int y);
	void connectRooms();
	void generateCorridor(int roomOne, int roomTwo);
	void generateCorridorAxis(bool first, int axis, int roomOne, int roomTwo, glm::ivec2& distance, glm::ivec2 startPos);
	void generateWalls() override;
	float CalculateDistance(glm::ivec2& v, glm::ivec2& w);

private:

	void swap(float& x, float& y);
	void sortCosts(std::vector<float>& mapkeys);
	glm::ivec2 parseConnections(std::string& string);
	//TODO: Maybe keep pointers to start/end and reward rooms

	LevelState* levelState;

private:
	//TODO: Read these from a .json file

	std::vector<std::shared_ptr<Room>> rooms;
	std::vector<int> roomsConnected;

	glm::vec2 tileSize;

	float roomVisibilityDistance;
	float scaleMultiplier;

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

	int amountOfFloorPrefabs;
	int amountOfWallPrefabs;

	char parserToken = '_';
};

#endif // ! NORMALDUNGEON
