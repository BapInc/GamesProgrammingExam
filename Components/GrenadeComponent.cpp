#include "GrenadeComponent.h"
#include <iostream>

GrenadeComponent::GrenadeComponent(GameObject* gameObject) : BulletComponent(gameObject)
{
	this->gameObject = gameObject;
}

void GrenadeComponent::shoot(float deltaTime)
{
	std::cout << "Granade";
}


