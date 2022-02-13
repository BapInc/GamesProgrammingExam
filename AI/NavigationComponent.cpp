#define GLM_ENABLE_EXPERIMENTAL
#include "NavigationComponent.h"
#include "glm/gtx/norm.hpp"

NavigationComponent::NavigationComponent(GameObject* gameObject)
	: Component(gameObject)
{
	this->gameObject = gameObject;
	physicsComponent = gameObject->getComponent<PhysicsComponent>();
}

void NavigationComponent::update(float deltaTime)
{
	if (!isPaused && hasPath)
		moveToDestination(deltaTime);
	else
		setRandomDestination(200);
}

void NavigationComponent::setRandomDestination(int moveLength)
{
	//TODO: make sure it's inside the bounds
	auto pos = gameObject->getTransform()->getPos();
	// Get a random direction
	auto randX = rand() % 3 - 1;
	int randY = 0;
	if (randX == 0)
	{
		while (randY == 0)
			randY = rand() % 3 - 1;
	}
	pos = { pos.x + randX * moveLength, pos.y + randY * moveLength };
	Debug::Log("x: " + std::to_string(randX) + " y: " + std::to_string(randY));
	destination = pos;

	hasPath = true;
}

void NavigationComponent::moveToDestination(float deltaTime)
{
	if (!hasPath)
	{
		Debug::Log("Tried to call moveToDestination without AI having a path set!", WARNING);
		return;
	}
	auto pos = gameObject->getTransform()->getPos();
	auto dir = glm::normalize(destination - pos);
	// length 2 returns the squared length 
	auto distance = glm::length2(pos - destination);
	if (distance <= 1)
		setRandomDestination(200);
	physicsComponent->setLinearVelocity(dir * movementSpeed);
}

void NavigationComponent::activateNavigation() {
	isPaused = false;
	initialPosition = gameObject->getTransform()->getPos();
}

void NavigationComponent::setValuesFromJSON(GenericValue<UTF8<char>, MemoryPoolAllocator<CrtAllocator>>* value)
{
	float speed = value->operator[]("movementSpeed").GetFloat();
	movementSpeed = speed;
}