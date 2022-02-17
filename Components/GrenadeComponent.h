#ifndef GRANADECOMPONENT_H
#define GRANADECOMPONENT_H

#include "../Components/BulletComponent.h"

class GrenadeComponent : public BulletComponent
{
public:
	explicit GrenadeComponent(GameObject* gameObject);
	void shoot(float deltaTime) override;

};
#endif
