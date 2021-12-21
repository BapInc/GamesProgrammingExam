#pragma once

#include "Component.h"
#include "sre/Sprite.hpp"
#include "SpriteComponent.h"

class SpriteAnimationComponent : public Component
{
public:
	SpriteAnimationComponent(GameObject* gameObject);

	void setSprites(std::vector<sre::Sprite> sprites);      // sprite sequence

	void update(float deltaTime) override;

	float getAnimationTime() const;                         // time between animations (in seconds)
	void setAnimationTime(float animationTime);
private:
	float animationTime = 0.300f;
	std::vector<sre::Sprite> sprites;
	float time = 0;
	int spriteIndex = 0;
};


