#include "BulletComponent.h"
#include <SDL_events.h>
#include <iostream>


BulletComponent::BulletComponent(GameObject* gameObject) : Component(gameObject)
{
	this->gameObject = gameObject;
}

void BulletComponent::shoot(sre::Sprite bullet, glm::vec2 pos, glm::vec2 vel, float rot) {

}

void BulletComponent::update(float deltaTime) {

}