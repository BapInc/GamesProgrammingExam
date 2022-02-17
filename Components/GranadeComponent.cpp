#include "GranadeComponent.h"
#include <iostream>

GranadeComponent::GranadeComponent(GameObject* gameObject) : BulletComponent(gameObject)
{
	this->gameObject = gameObject;
	std::cout << "Granadeskr";
}

void GranadeComponent::shoot(float deltaTime)
{
	std::cout << "Granade";
}


