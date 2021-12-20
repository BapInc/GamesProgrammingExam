#include "SpriteManager.hpp"

using namespace sre;
SpriteManager* SpriteManager::instance = nullptr;


SpriteManager::SpriteManager()
{
	instance = this;
	spriteAtlas = SpriteAtlas::create("spritesheet.json", "spritesheet.png");
}

std::shared_ptr<sre::Sprite> SpriteManager::getSprite(std::string spriteName)
{
	if(spriteMap.find(spriteName) == spriteMap.end())
	{
		spriteMap[spriteName] = spriteAtlas->get(spriteName);
	}
	return std::make_shared<sre::Sprite>(spriteMap[spriteName]);
}


SpriteManager* SpriteManager::getInstance()
{
	if(!instance)
		instance = new SpriteManager();
	return instance;
}
