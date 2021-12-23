#pragma once
#include "../Components/Component.h"
#include "../Game/SpriteManager.h"

class Player : public Component 
{

public:
	explicit Player(GameObject* gameObject);

	bool onKey(SDL_Event& event) override;
	void update(float deltaTime) override;

private:
	glm::vec2 velocity;

};