#include "GrenadeComponent.h"
#include "PhysicsComponent.h"
#include "../GameStates/LevelState.h"
#include <iostream>

GrenadeComponent::GrenadeComponent(GameObject* gameObject) : BulletComponent(gameObject)
{
	this->gameObject = gameObject;
	speed = 500.0f;
	lifetime = 100;
}

void GrenadeComponent::explosion(float deltaTime) {

	lifetime -= deltaTime;
	if (lifetime == 10) {
		explosive = levelState->loadPrefab("Explosive", gameObject->getTransform()->getPos());
	}

	if (lifetime <= 0) {
		explosive->setShouldDestroy(true);
		gameObject->setShouldDestroy(true);
	}
}


void GrenadeComponent::shoot(float deltaTime)
{
	if (speed > 0) {
		speed -= 20;
		gameObject->getComponent<PhysicsComponent>()->addForce(bulletDirection * speed * deltaTime);
	}
	else {
		explosion(deltaTime);
	}
}


