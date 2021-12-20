#ifndef TILEMAP_H
#define TILEMAP_H

#include <vector>
#include "Tile.h"
#include <map>
#include <string>

class TileMap
{
public:
	TileMap();
	TileMap(int width, int height, glm::vec2 pos);
	std::shared_ptr<Tile> getTileAt(glm::vec2 pos);
	void setPosition(glm::vec2 pos);
	std::vector<std::vector<std::shared_ptr<Tile>>> getTiles();

private:
	std::vector<std::vector<std::shared_ptr<Tile>>> tiles;
	glm::vec2 position = glm::vec2{ 0,0 };

};

#endif