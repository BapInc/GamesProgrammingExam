#pragma once
#include "../Components/Component.h"
#include "../GameStates/LevelState.h"
#include "../Game/GameObject.h"
#include "../Commands/MoveCommand.h"
#include "../Components/SpriteComponent.h"

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
	void start();

private:
	float speed;
	glm::vec2 velocity;
	//MoveCommand* moveCommand;
	std::stack<std::shared_ptr<MoveCommand>> moveCommands;
	std::shared_ptr<SpriteComponent> spriteComponent;
	std::shared_ptr<GameObject> weapon1;
	std::shared_ptr<GameObject> weapon2;
	LevelState* levelState;
	bool facingRight = true;
	bool test = true;
};