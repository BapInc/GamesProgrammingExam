#pragma once
#include "../Components/Component.h"
#include "../GameStates/LevelState.h"
#include "../Game/GameObject.h"
#include "../Commands/MoveCommand.h"
#include "../Components/SpriteComponent.h"
#include "../GameStates/LevelState.h"
#include "../Components/AudioComponent.h"

class Player : public Component
{

public:

	explicit Player(GameObject* gameObject);

public:
	void start();
	bool onKey(SDL_Event& event) override;
	void update(float deltaTime) override;
	void setValuesFromJSON(GenericValue<UTF8<char>, MemoryPoolAllocator<CrtAllocator>>* value, GameState* state);
	void setLevel(LevelState& levelState);
	void setAudio(AudioComponent& audio);
	void addWeapon();
	bool getFacing();
	void selectWeapon(int keyboardNumber);
	void loadSprites();
	void updateAnimations(float deltaTime);
	void setSpriteComponent(std::shared_ptr<SpriteComponent> spriteComponent);
	std::shared_ptr<GameObject> Player::selectedWeapon();
	glm::vec2 setMouseDirection();
	void onCollisionStart(PhysicsComponent* comp) override;
private:
	//MoveCommand* moveCommand;
	std::stack<std::shared_ptr<MoveCommand>> moveCommands;
	std::shared_ptr<SpriteComponent> spriteComponent;
	std::shared_ptr<PhysicsComponent> physicsComponent;
	LevelState* levelState;
	AudioComponent* audio;

	//Weapons
	std::vector<std::shared_ptr<GameObject>> weaponInventory;
	std::shared_ptr<GameObject> weapon1;
	std::shared_ptr<GameObject> weapon2;
	std::shared_ptr<GameObject> bullet;

	//Player movements
	float speed;
	glm::vec2 velocity;
	bool facingRight = true;
	bool pressed = false;

	//Animations
	std::vector<char*> idleAnimations;
	std::vector<char*> runningAnimations;
	sre::Sprite currentSprite;
	glm::vec2 scale;
	float animationTime = 0.100f;
	float time = 0;
	int spriteIndex = 0;

	//Mouse coordinates
	int x, y;
	int originX, originY;
};