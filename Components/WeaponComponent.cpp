#include "WeaponComponent.h"
#include "..\Player\Player.h"
#include <SDL_events.h>
#include <iostream>


WeaponComponent::WeaponComponent(GameObject* gameObject) : Component(gameObject)
{
	this->gameObject = gameObject;
}

void WeaponComponent::setPlayer(GameObject& player) {
	this->player = &player;
}

void WeaponComponent::setValuesFromJSON(GenericValue<UTF8<char>, MemoryPoolAllocator<CrtAllocator>>* value, GameState* state)
{

}

bool WeaponComponent::flipWeapon() {
	return player->getComponent<Player>()->getFacing();
}

void WeaponComponent::update(float deltaTime) {
	auto newPos = player->getTransform()->getPos();
	if (flipWeapon()) {
		gameObject->getTransform()->SetPos(newPos + glm::vec2(10,-15));
	}
	else {
		gameObject->getTransform()->SetPos(newPos + glm::vec2(-10, -15));
	}
}