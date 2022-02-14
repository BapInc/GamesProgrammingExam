#ifndef NAVIGATIONCOMPONENT_H
#define NAVIGATIONCOMPONENT_H

#include "../Components/Component.h"
#include "../Components/PhysicsComponent.h"
#include "../Game/GameObject.h"
#include "fmod_studio.h"
#include "fmod.h"
#include "../Managers/AudioManager.h"
#include "../GameStates/GameState.h"

class NavigationComponent : public Component
{
public:
	explicit NavigationComponent(GameObject* gameObject);
	void update(float deltaTime) override;
	void setDestination(glm::vec2 position);
	void setRandomDestination(int moveLength);
	void moveToDestination(float deltaTime);
	void activateNavigation();
	void setValuesFromJSON(GenericValue<UTF8<char>, MemoryPoolAllocator<CrtAllocator>>* value);
	void setMovementSpeed(float speed);
	std::shared_ptr<NavigationComponent> clone(GameObject* gameObject);



private:
	bool hasPath = false;
	bool isPaused = true;
	float movementSpeed = 10.0f;
	glm::vec2 initialPosition = { 0,0 };

	glm::vec2 destination = { 0,0 };
	std::shared_ptr<PhysicsComponent> physicsComponent;
};

#endif