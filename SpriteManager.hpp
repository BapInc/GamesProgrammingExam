#ifndef SPRITEMANAGER_H
#define SPRITEMANAGER_H

#include <map>
#include "GameState.h"
#include "Box2DDebugDraw.hpp"
#include "sre/SpriteAtlas.hpp"
#include "PhysicsComponent.hpp"
#include "Box2D/Dynamics/b2World.h"
#include "TopDownCameraComponent.h"


class SpriteManager 
{
public:
	SpriteManager();
	static SpriteManager* getInstance();


	std::shared_ptr<sre::Sprite> SpriteManager::getSprite(std::string spriteName);
private:
	static SpriteManager* instance;
	std::map<std::string, sre::Sprite> spriteMap;

	std::shared_ptr<sre::SpriteAtlas> spriteAtlas;

	std::vector<std::shared_ptr<GameObject>> sceneObjects;
};

#endif;
