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
	void setLevel(LevelState& level);

	bool onKey(SDL_Event& event) override;
	void update(float deltaTime) override;
	void setValuesFromJSON(GenericValue<UTF8<char>, MemoryPoolAllocator<CrtAllocator>>* value, GameState* state);

	std::unique_ptr<LevelState> level;
	

private:
	float speed;
	glm::vec2 velocity;
	//MoveCommand* moveCommand;
	std::stack<std::shared_ptr<MoveCommand>> moveCommands;
	std::shared_ptr<SpriteComponent> spriteComponent;
	bool facingRight = true;
};