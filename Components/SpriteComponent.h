#ifndef SPRITECOMPONENT_H
#define SPRITECOMPONENT_H

#include "Component.h"
#include "sre/Sprite.hpp"
#include "../GameStates/GameState.h"
using namespace rapidjson;

class SpriteComponent : public Component
{
public:
	explicit SpriteComponent(GameObject* gameObject);

	void renderSprite(sre::SpriteBatch::SpriteBatchBuilder& spriteBatchBuilder) override;

	void setSprite(const sre::Sprite& sprite);

	sre::Sprite getSprite();

	void setValuesFromJSON(GenericValue<UTF8<char>, MemoryPoolAllocator<CrtAllocator>>* value, GameState* state);

	void flipSprite(bool flip);

private:
	sre::Sprite sprite;
};

#endif