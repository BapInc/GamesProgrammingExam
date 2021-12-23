#include "Player.h"
#include <SDL_events.h>
#include <iostream>
#include "../Game/GameObject.h"
#include "../Components/SpriteComponent.h"

using namespace std;


Player::Player(GameObject* gameObject) : Component(gameObject)
{
    this->gameObject = gameObject;
}

void Player::setLevel(LevelState& level)
{
    this->level = std::make_unique<LevelState>(level);
}

bool Player::onKey(SDL_Event& event) {
    switch (event.key.keysym.sym) {
    case SDLK_w:
        cout << "Hello World!";
        velocity.y = event.type == SDL_KEYDOWN ? 1 : 0;
        break;
    case SDLK_s:
        cout << "Hello World!";
        velocity.y = event.type == SDL_KEYDOWN ? -1 : 0;
        break;
    case SDLK_a:
        cout << "Hello World!";
        velocity.x = event.type == SDL_KEYDOWN ? -1 : 0;
        break;
    case SDLK_d:
        cout << "Hello World!";
        velocity.x = event.type == SDL_KEYDOWN ? 1 : 0;
        break;
    }
    return true;
}

void Player::update(float deltaTime) {
    float speed = 100;
    auto newPos = gameObject->getPosition() + velocity * speed * deltaTime;

    gameObject->setPosition(newPos);
}