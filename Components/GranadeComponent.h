#ifndef GRANADECOMPONENT_H
#define GRANADECOMPONENT_H

#include "../Components/BulletComponent.h"

class GranadeComponent : public BulletComponent
{
public:
	explicit GranadeComponent(GameObject* gameObject);
	void shoot(float deltaTime) override;

};
#endif
