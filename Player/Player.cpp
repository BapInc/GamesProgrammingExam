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

void Player::start() {
	weapon1 = levelState->loadPrefab("Weapon1", gameObject->getTransform()->getPos());
	levelState->createGameObject(weapon1.get());
	weapon1->getComponent<WeaponComponent>()->setPlayer(*gameObject);

	weapon2 = levelState->loadPrefab("Weapon2", gameObject->getTransform()->getPos());
	levelState->createGameObject(weapon2.get());
	weapon2->getComponent<WeaponComponent>()->setPlayer(*gameObject);
	weapon2->setActive(false);
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
		weapon1->setActive(true);
		weapon2->setActive(false);
		break;
	case SDLK_2:
		weapon1->setActive(false);
		weapon2->setActive(true);
		break;
	case SDLK_SPACE:
		//press 1 -> bullet = granade
		//press 2 -> bullet = other bullet
		//shoot(bullet)
		break;
	}

	return true;
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