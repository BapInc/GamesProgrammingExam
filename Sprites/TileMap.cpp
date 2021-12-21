#include "TileMap.h"
#include "../Game/SpriteManager.h"
#include <iostream>

TileMap::TileMap()
{
}

TileMap::TileMap(int width, int height, glm::vec2 pos)
{
	tiles.resize(width);
	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			auto sprite = SpriteManager::getInstance()->getSprite("floor_1.png");
			sprite->setPosition(pos + glm::vec2{ x * sprite->getSpriteSize().x, y * sprite->getSpriteSize().y });
			tiles[x].push_back(std::make_shared<Tile>(sprite, true));
		}
	}
}

std::shared_ptr<Tile> TileMap::getTileAt(glm::vec2 pos)
{
	return tiles[pos.x][pos.y];
}

std::vector<std::vector<std::shared_ptr<Tile>>> TileMap::getTiles()
{
	return tiles;
}


