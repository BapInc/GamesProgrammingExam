#include "BulletComponent.h"
#include <SDL_events.h>
#include <iostream>
#include "../Game/DungeonGame.h"


BulletComponent::BulletComponent(GameObject* gameObject) : Component(gameObject)
{
	this->gameObject = gameObject;
}

void BulletComponent::setBulletDirection(glm::vec2 mouseDir) {
	bulletDirection = mouseDir;
}

void BulletComponent::update(float deltaTime) {
	gameObject->getTransform()->SetPos(gameObject->getTransform()->getPos() + bulletDirection * speed * deltaTime);

	//if type addforce on json -> addforce()
	//else if type normalshooting on json -> normalshooting()
}