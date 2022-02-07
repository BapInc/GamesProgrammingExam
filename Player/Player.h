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

	std::unique_ptr<LevelState> level;
	

private:
	glm::vec2 velocity;
	//MoveCommand* moveCommand;
	std::stack<std::shared_ptr<MoveCommand>> moveCommands;
	std::shared_ptr<SpriteComponent> spriteComponent;
	bool facingRight = true;
};