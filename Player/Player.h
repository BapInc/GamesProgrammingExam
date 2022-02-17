#pragma once
#include "../Components/Component.h"
#include "../GameStates/LevelState.h"
#include "../Game/GameObject.h"
#include "../Commands/MoveCommand.h"
#include "../Components/SpriteComponent.h"
#include "../GameStates/LevelState.h"

class Player : public Component
{

public:

	explicit Player(GameObject* gameObject);

public:
	void setLevel(LevelState& levelState);

	bool onKey(SDL_Event& event) override;
	void update(float deltaTime) override;
	void setValuesFromJSON(GenericValue<UTF8<char>, MemoryPoolAllocator<CrtAllocator>>* value, GameState* state);
	bool getFacing();
	void addWeapon();
	void selectWeapon(int keyboardNumber);
	std::shared_ptr<GameObject> Player::selectedWeapon();
	glm::vec2 setMouseDirection();

private:
	//MoveCommand* moveCommand;
	std::stack<std::shared_ptr<MoveCommand>> moveCommands;
	std::shared_ptr<SpriteComponent> spriteComponent;
	LevelState* levelState;

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

	//Mouse coordinates
	int x, y;
	int originX, originY;
};