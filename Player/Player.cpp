#include "Player.h"
#include <SDL_events.h>
#include <iostream>
#include "../Game/GameObject.h"
#include "../Commands/MoveCommand.h"
#include "glm/glm.hpp"
#include "../Components/WeaponComponent.h"

Player::Player(GameObject* gameObject) : Component(gameObject)
{
	this->gameObject = gameObject;
	spriteComponent = gameObject->getComponent<SpriteComponent>();
	//moveCommand = NULL;
}

void Player::setLevel(LevelState& levelState)
{
	this->levelState = &levelState;
}

void Player::addWeapon() {
	weapon1 = levelState->loadPrefab("Weapon1");
	levelState->createGameObject(weapon1.get());
	weapon1->getComponent<WeaponComponent>()->setPlayer(*gameObject);
	weapon1->getComponent<WeaponComponent>()->setLevel(*levelState);

	weapon2 = levelState->loadPrefab("Weapon2");
	levelState->createGameObject(weapon2.get());
	weapon2->getComponent<WeaponComponent>()->setPlayer(*gameObject);
	weapon2->getComponent<WeaponComponent>()->setLevel(*levelState);
	weapon2->setActive(false);

	weaponInventory.push_back(weapon1);
	weaponInventory.push_back(weapon2);
}

bool Player::onKey(SDL_Event& event) {
	bool temp = true;
	switch (event.key.keysym.sym) {
	case SDLK_w:
		velocity.y = event.type == SDL_KEYDOWN ? 1 : 0;
		//moveCommands.push(std::shared_ptr<MoveCommand>(new MoveCommand(gameObject->getPosition())));
		break;
	case SDLK_s:
		velocity.y = event.type == SDL_KEYDOWN ? -1 : 0;
		break;
	case SDLK_a:
		velocity.x = event.type == SDL_KEYDOWN ? -1 : 0;
		if (getFacing()) {
			spriteComponent->flipSprite(true);
			facingRight = false;
		}
		break;
	case SDLK_d:
		velocity.x = event.type == SDL_KEYDOWN ? 1 : 0;
		if (!getFacing()) {
			spriteComponent->flipSprite(false);
			facingRight = true;
		}
		break;
	case SDLK_1:
		selectWeapon(1);
		break;
	case SDLK_2:
		selectWeapon(2);
		break;
	case SDLK_SPACE:

		if (event.type == SDL_KEYDOWN && pressed == false) {

			pressed = true;

			auto bullet = selectedWeapon()->getComponent<WeaponComponent>()->getBulletType();
		}
	
		//shoot(bullet, player pos, mouse dir, mouse rot)

		if (event.type == SDL_KEYUP) {
			pressed = false;
		}
		break;
	}

	return true;
}

void Player::selectWeapon(int keyboardNumber) {
	for (int i = 0; i < weaponInventory.size(); i++) {
		if (i == keyboardNumber - 1) {
			weaponInventory[i]->setActive(true);
		}
		else {
			weaponInventory[i]->setActive(false);
		}
	}
}

std::shared_ptr<GameObject> Player::selectedWeapon() {
	for (int i = 0; i < weaponInventory.size(); i++) {
		if (weaponInventory[i]->getActive()) {
			return weaponInventory[i];
		}
	}
}

void Player::shoot() {

}

bool Player::getFacing() {
	return facingRight;
}

void Player::setValuesFromJSON(GenericValue<UTF8<char>, MemoryPoolAllocator<CrtAllocator>>* value, GameState* state)
{
	speed = value->operator[]("speed").GetFloat();
	velocity.x = value->operator[]("velocity")["x"].GetFloat();
	velocity.y = value->operator[]("velocity")["y"].GetFloat();
}

void Player::update(float deltaTime) {

	auto newPos = gameObject->getTransform()->getPos() + velocity * speed * deltaTime;

	gameObject->getTransform()->SetPos(newPos);
}