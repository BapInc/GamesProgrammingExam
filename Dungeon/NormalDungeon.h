#ifndef NORMAL_DUNGEON
#define NORMAL_DUNGEON

#include "Dungeon.h"
class NormalDungeon : public Dungeon
{
public:
	NormalDungeon();

protected:

	void generateRooms() override;
};

#endif // ! NORMALDUNGEON
