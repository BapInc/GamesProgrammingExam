#include "DungeonGame.h"

int main()
{
#ifdef _DEBUG
	std::cout << "Starting Dungeon Game" << std::endl;
#endif
	new DungeonGame();
	return 0;
}