#include "WeaponComponent.h"
#include <SDL_events.h>
#include <iostream>


WeaponComponent::WeaponComponent(GameObject* gameObject) : Component(gameObject)
{
	this->gameObject = gameObject;
}

void WeaponComponent::setPlayer(std::shared_ptr<GameObject> player) {
	this->player = player;
}

void WeaponComponent::setValuesFromJSON(GenericValue<UTF8<char>, MemoryPoolAllocator<CrtAllocator>>* value, GameState* state)
{

}

void WeaponComponent::update(float deltaTime) {

	auto newPos = player->getTransform()->getPos();

	gameObject->getTransform()->SetPos(newPos + glm::vec2(10,-15));
}