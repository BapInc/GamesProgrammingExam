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
		setRandomDestination(30, 30);
}

void NavigationComponent::setRandomDestination(int minDistance, int maxDistance)
{
	//TODO: make sure it's inside the bounds
	auto pos = gameObject->getTransform()->getPos();
	pos += rand() % maxDistance + minDistance;
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
	Debug::Log(std::to_string(distance));
	if (distance <= 1)
		setRandomDestination(30, 30);

	Debug::Log(std::to_string(distance));
	physicsComponent->setLinearVelocity(dir * movementSpeed);
}

void NavigationComponent::setValuesFromJSON(GenericValue<UTF8<char>, MemoryPoolAllocator<CrtAllocator>>* value)
{
	float speed = value->operator[]("movementSpeed").GetFloat();
	movementSpeed = speed;
}