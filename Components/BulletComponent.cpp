#include "BulletComponent.h"
#include <SDL_events.h>
#include <iostream>
#include "../Game/DungeonGame.h"
#include "PhysicsComponent.h"
#include "../GameStates/LevelState.h"

BulletComponent::BulletComponent(GameObject* gameObject) : Component(gameObject)
{
	this->gameObject = gameObject;
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
}

void BulletComponent::update(float deltaTime) {
	// TODO: Save and resuse component
	shoot(deltaTime);
	//gameObject->getTransform()->SetPos(gameObject->getTransform()->getPos() + bulletDirection * speed * deltaTime);
	//if type addforce on json -> addforce()
	//else if type normalshooting on json -> normalshooting()
}

