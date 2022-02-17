#include "WeaponComponent.h"
#include "..\Player\Player.h"
#include <SDL_events.h>
#include <iostream>
#include "../Utility/Debug.h"
#include "../Game/DungeonGame.h"
#include <cmath>
# define PI           3.14159265358979323846


WeaponComponent::WeaponComponent(GameObject* gameObject) : Component(gameObject)
{
	this->gameObject = gameObject;
	originX = DungeonGame::getInstance()->getWindowSize().x / 2;
	originY = DungeonGame::getInstance()->getWindowSize().y / 2;
}

void WeaponComponent::setPlayer(GameObject& player) {
	this->player = &player;
}

void WeaponComponent::setLevel(LevelState& levelState)
{
	this->levelState = &levelState;
}

void WeaponComponent::setValuesFromJSON(GenericValue<UTF8<char>, MemoryPoolAllocator<CrtAllocator>>* value, GameState* state)
{
	bullet = value->operator[]("bullet").GetString();
}

std::shared_ptr<GameObject> WeaponComponent::getBulletType() {
	bulletType = levelState->loadPrefab(bullet);
	auto b = levelState->createGameObject(bulletType.get());
	b->getTransform()->SetPos(gameObject->getTransform()->getPos());
	return b;
}

bool WeaponComponent::flipWeapon() {
	return player->getComponent<Player>()->getFacing();
}

float& WeaponComponent::getMouseRotation() {
	SDL_GetMouseState(&x, &y);
	radians = std::atan2(x - originX, -y + originY);
	angle = -(radians * 180 / PI);

	return angle;
}


void WeaponComponent::update(float deltaTime) {
	auto newPos = player->getTransform()->getPos();
	if (flipWeapon()) {
		gameObject->getTransform()->SetPos(newPos + glm::vec2(10, -15));
	}
	else {
		gameObject->getTransform()->SetPos(newPos + glm::vec2(-10, -15));
	}
	gameObject->getTransform()->Rotate(getMouseRotation());
}