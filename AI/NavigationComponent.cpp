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
	if (!isPaused && hasPath) {
		moveToDestination(deltaTime);
		updateAnimations(deltaTime);
	}
	else if (!isPaused)
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
	destination = pos;
	//Debug::Log("Dir: " + std::to_string(randX) + " " + std::to_string(randY));
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
	if (dir.x > 0) {
		facingRight = true;
	}
	else {
		facingRight = false;
	}
	// length 2 returns the squared length 
	auto distance = glm::length2(pos - destination);
	if (distance <= 1)
		setRandomDestination(200);
	physicsComponent->setLinearVelocity(dir * movementSpeed);
	//Debug::Log(std::to_string(physicsComponent->getLinearVelocity().x) + " " + std::to_string(physicsComponent->getLinearVelocity().y));
}

void NavigationComponent::activateNavigation() {
	srand(time(NULL));
	physicsComponent = gameObject->getComponent<PhysicsComponent>();
	spriteComponent = gameObject->getComponent<SpriteComponent>();
	initialPosition = gameObject->getTransform()->getPos();
	isPaused = false;
	loadSprites();
}

void NavigationComponent::setLevel(LevelState& levelState)
{
	this->levelState = &levelState;
}

void NavigationComponent::loadSprites() {
	//Running Animations
	char* run1 = "big_demon_run_anim_f0.png";
	char* run2 = "big_demon_run_anim_f1.png";
	char* run3 = "big_demon_run_anim_f2.png";
	char* run4 = "big_demon_run_anim_f3.png";
	runningAnimations.push_back(run1);
	runningAnimations.push_back(run2);
	runningAnimations.push_back(run3);
	runningAnimations.push_back(run4);
}

void NavigationComponent::updateAnimations(float deltaTime) {
	animTime += deltaTime;
	if (animTime > animationTime) {
		animTime = fmod(animTime, animationTime);
		spriteIndex = (spriteIndex + 1) % runningAnimations.size();
		currentSprite = levelState->getSprite(runningAnimations[spriteIndex]);
		currentSprite.setScale(gameObject->getTransform()->getScale());
		spriteComponent->setSprite(currentSprite);
		spriteComponent->flipSprite(!facingRight);
	}
}

void NavigationComponent::onCollisionStart(PhysicsComponent* comp)
{

	if (comp->getGameObject()->getName() == "Bullet2")
	{
		takeDamage(25);
		if (health <= 0) {
 			gameObject->setShouldDestroy(true);
		}
	}
	if (comp->getGameObject()->getName() == "Explosive")
	{
		takeDamage(50);
		if (health <= 0) {
			gameObject->setShouldDestroy(true);
		}
	}
}

void NavigationComponent::takeDamage(int damage) {
	health -= damage;
}

void NavigationComponent::setValuesFromJSON(GenericValue<UTF8<char>, MemoryPoolAllocator<CrtAllocator>>* value)
{
	float speed = value->operator[]("movementSpeed").GetFloat();
	movementSpeed = speed;
}

std::shared_ptr<NavigationComponent> NavigationComponent::clone(GameObject* gameObject)
{
	auto clone = std::shared_ptr<NavigationComponent>(new NavigationComponent(*this));
	clone->gameObject = gameObject;
	return clone;
}
