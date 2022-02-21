#ifndef GRANADECOMPONENT_H
#define GRANADECOMPONENT_H

#include "../Components/BulletComponent.h"

class GrenadeComponent : public BulletComponent
{
public:
	explicit GrenadeComponent(GameObject* gameObject);
	void shoot(float deltaTime) override;
	void explosion(float deltaTime);
	void updateAnimation(float deltaTime);
	void onCollisionStart(PhysicsComponent* comp) override;

private:
	std::shared_ptr<GameObject> explosive;
	std::vector<char*> grenadeAnimations;
	sre::Sprite currentSprite;
	glm::vec2 scale;
	float animationTime = 0.100f;
	float time = 0;
	int spriteIndex = 0;
};
#endif
