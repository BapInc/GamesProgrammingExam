#ifndef GRANADECOMPONENT_H
#define GRANADECOMPONENT_H

#include "../Components/BulletComponent.h"

class GrenadeComponent : public BulletComponent
{
public:
	explicit GrenadeComponent(GameObject* gameObject);
	void shoot(float deltaTime) override;
	void explosion(float deltaTime);
	void exploded(std::shared_ptr<GameObject> gameObject, float deltaTime);

private:
	std::shared_ptr<GameObject> explosive;
};
#endif
