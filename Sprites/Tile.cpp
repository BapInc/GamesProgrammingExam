#include "Tile.h"
#include "../Utility/Debug.h"
Tile::Tile()
{
	Debug::Log("CREATED TILE");
}

Tile::Tile(std::shared_ptr<sre::Sprite> sprite, bool isWalkable)
{
	this->sprite = *sprite;
	this->isWalkable = isWalkable;
}

sre::Sprite Tile::getSprite()
{
	return sprite;
}
