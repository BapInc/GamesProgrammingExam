#ifndef SPRITEMANAGER_H
#define SPRITEMANAGER_H

#include <map>
#include "../GameStates/GameState.h"
#include "../Utility/Box2DDebugDraw.h"
#include "sre/SpriteAtlas.hpp"
#include "../Components/PhysicsComponent.h"
#include "Box2D/Dynamics/b2World.h"
#include "../Components/TopDownCameraComponent.h"


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

};

#endif;
