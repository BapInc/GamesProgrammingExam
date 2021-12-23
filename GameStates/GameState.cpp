#include "GameState.h"
#include "../Utility/Debug.h"

GameState::GameState()
{
}

void GameState::loadSpriteSheet(char* json, char* png)
{
	spriteAtlas = sre::SpriteAtlas::create(json, png);
}

sre::Sprite GameState::getSprite(char* spriteName)
{
	if (spriteAtlas == nullptr)
	{
		Debug::Log("Must load Sprite Sheet before trying to get sprites", Logs::ALERT);
	}
	return spriteAtlas->get(spriteName);
}

