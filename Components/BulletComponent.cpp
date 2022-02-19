#include "BulletComponent.h"
#include <SDL_events.h>
#include <iostream>
#include "../Game/DungeonGame.h"
#include "PhysicsComponent.h"
#include "../GameStates/LevelState.h"

BulletComponent::BulletComponent(GameObject* gameObject) : Component(gameObject)
{
	this->gameObject = gameObject;
	lifetime = 30;
	speed = 500.0f;
	physicsComponent = gameObject->getComponent<PhysicsComponent>();
}

void BulletComponent::setBulletDirection(glm::vec2 mouseDir) {
	bulletDirection = mouseDir;
}

void BulletComponent::setLevel(LevelState& levelState)
{
	this->levelState = &levelState;
}

void BulletComponent::shoot(float deltaTime)
{
	gameObject->getComponent<PhysicsComponent>()->moveTo(gameObject->getTransform()->getPos() + bulletDirection * (speed / LevelState::physicsScale) * deltaTime);
	lifetime -= deltaTime;
	if (lifetime <= 0) {
		gameObject->setShouldDestroy(true);
	}
}

void BulletComponent::update(float deltaTime) {
	shoot(deltaTime);
}

