#include "Player.h"
#include <SDL_events.h>
#include <iostream>
#include "../Game/GameObject.h"
#include "../Commands/MoveCommand.h"
#include "glm/glm.hpp"
#include "../Components/WeaponComponent.h"
#include "../Components/BulletComponent.h"
#include "../Game/DungeonGame.h"

Player::Player(GameObject* gameObject) : Component(gameObject)
{
	this->gameObject = gameObject;
	spriteComponent = gameObject->getComponent<SpriteComponent>();
	originX = DungeonGame::getInstance()->getWindowSize().x / 2;
	originY = DungeonGame::getInstance()->getWindowSize().y / 2;
	//moveCommand = NULL;
}

void Player::setLevel(LevelState& levelState)
{
	this->levelState = &levelState;
}

void Player::setAudio(AudioComponent& audio)
{
	this->audio = &audio;
}

void Player::start() {
	addWeapon();
	loadSprites();
}

void Player::addWeapon() {
	weapon1 = levelState->loadPrefab("Weapon1", gameObject->getTransform()->getPos());
	weapon1->getComponent<WeaponComponent>()->setPlayer(*gameObject);
	weapon1->getComponent<WeaponComponent>()->setLevel(*levelState);

	weapon2 = levelState->loadPrefab("Weapon2", gameObject->getTransform()->getPos());
	weapon2->getComponent<WeaponComponent>()->setPlayer(*gameObject);
	weapon2->getComponent<WeaponComponent>()->setLevel(*levelState);
	weapon2->setActive(false);

	weaponInventory.push_back(weapon1);
	weaponInventory.push_back(weapon2);
}

void Player::loadSprites() {

	//Idle Animations
	char* idle1 = "lizard_f_idle_anim_f0.png";
	char* idle2 = "lizard_f_idle_anim_f1.png";
	char* idle3 = "lizard_f_idle_anim_f2.png";
	char* idle4 = "lizard_f_idle_anim_f3.png";
	idleAnimations.push_back(idle1);
	idleAnimations.push_back(idle2);
	idleAnimations.push_back(idle3);
	idleAnimations.push_back(idle4);

	//Running Animations
	char* run1 = "lizard_f_run_anim_f0.png";
	char* run2 = "lizard_f_run_anim_f1.png";
	char* run3 = "lizard_f_run_anim_f2.png";
	char* run4 = "lizard_f_run_anim_f3.png";
	runningAnimations.push_back(run1);
	runningAnimations.push_back(run2);
	runningAnimations.push_back(run3);
	runningAnimations.push_back(run4);
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
			facingRight = false;
		}
		break;
	case SDLK_d:
		velocity.x = event.type == SDL_KEYDOWN ? 1 : 0;
		if (!getFacing()) {
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
			audio->playSound("shoot");
			auto temp = selectedWeapon()->getComponent<WeaponComponent>()->getBulletType();

			temp->getComponent<BulletComponent>()->setBulletDirection(setMouseDirection());
			temp->getComponent<BulletComponent>()->setLevel(*levelState);
			temp->getComponent<BulletComponent>()->setAudio(*audio);
		}

		if (event.type == SDL_KEYUP) {
			pressed = false;
		}
		break;
	}

	return true;
}

void Player::updateAnimations(float deltaTime) {

	time += deltaTime;
	if (time > animationTime) {
		time = fmod(time, animationTime);
		if (velocity == glm::vec2(0.0f)) {
				spriteIndex = (spriteIndex + 1) % idleAnimations.size();
				currentSprite = levelState->getSprite(idleAnimations[spriteIndex]);
		}
		else {
			spriteIndex = (spriteIndex + 1) % runningAnimations.size();
			currentSprite = levelState->getSprite(runningAnimations[spriteIndex]);
			if (spriteIndex % 2 == 0) {
				audio->playSound("run");
			}
		}
		currentSprite.setScale(gameObject->getTransform()->getScale());
		spriteComponent->setSprite(currentSprite);
		spriteComponent->flipSprite(!getFacing());
	}
}

glm::vec2 Player::setMouseDirection() {
	SDL_GetMouseState(&x, &y);
	return glm::normalize(glm::vec2(x - originX, -y + originY));
}

void Player::setSpriteComponent(std::shared_ptr<SpriteComponent> spriteComponent)
{
	this->spriteComponent = spriteComponent;
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

	auto newPos = gameObject->getTransform()->getPos() + velocity * (speed / LevelState::physicsScale) * deltaTime;
	gameObject->getComponent<PhysicsComponent>()->moveTo(newPos);
	updateAnimations(deltaTime);
}