#ifndef SPRITECOMPONENT_H
#define SPRITECOMPONENT_H

#include "Component.h"
#include "sre/Sprite.hpp"

class SpriteComponent : public Component
{
public:
	explicit SpriteComponent(GameObject* gameObject);

	void renderSprite(sre::SpriteBatch::SpriteBatchBuilder& spriteBatchBuilder) override;

	void setSprite(const sre::Sprite& sprite);
	sre::Sprite getSprite();
private:
	sre::Sprite sprite;
};

#endif