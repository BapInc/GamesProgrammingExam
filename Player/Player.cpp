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
	//moveCommand = NULL;
}

void Player::setLevel(LevelState& level)
{
	this->level = std::make_unique<LevelState>(level);
}

bool Player::onKey(SDL_Event& event) {
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
		break;
	case SDLK_d:
		velocity.x = event.type == SDL_KEYDOWN ? 1 : 0;
		break;
	case SDLK_SPACE:

		break;
	}

	//gameObject->setPosition();

	return true;
}

void Player::update(float deltaTime) {
	float speed = 100;
	auto newPos = gameObject->getPosition() + velocity * speed * deltaTime;

	gameObject->setPosition(newPos);
}