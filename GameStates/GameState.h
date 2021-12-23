#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <vector>
#include <memory>
#include "../Game/GameObject.h"
#include "sre/SpriteAtlas.hpp"

class GameState
{
public:
	GameState();

	virtual void update(float time) = 0;
	virtual void render() = 0;
	virtual void start() = 0;
	virtual void onKey() = 0;

	void loadSpriteSheet(char* json, char* png);
	sre::Sprite getSprite(char* spriteName);

private:
	std::shared_ptr<sre::SpriteAtlas> spriteAtlas;
};

#endif