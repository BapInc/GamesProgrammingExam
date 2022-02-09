#include "Player.h"
#include <SDL_events.h>
#include <iostream>
#include "../Game/GameObject.h"
#include "../Components/SpriteComponent.h"
#include "../Commands/MoveCommand.h"
#include "glm/glm.hpp"

Player::Player(GameObject* gameObject) : Component(gameObject), velocity(0)
{
	this->gameObject = gameObject;
	spriteComponent = gameObject->getComponent<SpriteComponent>();
	//moveCommand = NULL;
}

void Player::setLevel(LevelState& level)
{
	this->level = std::make_unique<LevelState>(level);
}

bool Player::onKey(SDL_Event& event) {
	spriteComponent = gameObject->getComponent<SpriteComponent>();
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
		if (facingRight) {
			spriteComponent->flipSprite(true);
			facingRight = false;
		}
		break;
	case SDLK_d:
		velocity.x = event.type == SDL_KEYDOWN ? 1 : 0;
		if (!facingRight) {
			spriteComponent->flipSprite(false);
			facingRight = true;
		}
		break;
	case SDLK_SPACE:

		break;
	}

	return true;
}

void Player::setValuesFromJSON(GenericValue<UTF8<char>, MemoryPoolAllocator<CrtAllocator>>* value, GameState* state)
{
	speed = value->operator[]("speed").GetFloat();
}

void Player::update(float deltaTime) {

	auto newPos = gameObject->getTransform()->getPos() + velocity * speed * deltaTime;

	gameObject->getTransform()->SetPos(newPos);
}