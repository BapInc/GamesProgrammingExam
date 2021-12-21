#pragma once
#include <sre/Sprite.hpp>

class Tile
{
public:
	Tile();
	Tile(std::shared_ptr<sre::Sprite> sprite, bool isWalkable);
	sre::Sprite getSprite();

private:
	sre::Sprite sprite;

	bool isWalkable = false;


};