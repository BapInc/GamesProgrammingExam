#include "GrenadeComponent.h"
#include "PhysicsComponent.h"
#include "../GameStates/LevelState.h"
#include <iostream>

GrenadeComponent::GrenadeComponent(GameObject* gameObject) : BulletComponent(gameObject)
{
	this->gameObject = gameObject;
	gameObject->setTag("Grenade");
	speed = 500.0f;
	lifetime = 100;

	char* grenade1 = "flask_big_blue.png";
	char* grenade2 = "flask_big_red.png";

	grenadeAnimations.push_back(grenade1);
	grenadeAnimations.push_back(grenade2);
}

void GrenadeComponent::explosion(float deltaTime) {

	lifetime -= deltaTime;
	if (lifetime == 10) {
		explosive = levelState->loadPrefab("Explosive", gameObject->getTransform()->getPos());
		audio->playSound("explosion");
	}

	if (lifetime <= 0) {
		explosive->setShouldDestroy(true);
		gameObject->setShouldDestroy(true);
	}
}


void GrenadeComponent::shoot(float deltaTime)
{
	if (speed > 0) {
		speed -= 20;
		gameObject->getComponent<PhysicsComponent>()->addForce(bulletDirection * speed * deltaTime);
	}
	else {
		explosion(deltaTime);
		updateAnimation(deltaTime);
	}
}

void GrenadeComponent::onCollisionStart(PhysicsComponent* comp)
{

}

void GrenadeComponent::updateAnimation(float deltaTime) {
	time += deltaTime;
	if (time > animationTime) {
		time = fmod(time, animationTime);
		spriteIndex = (spriteIndex + 1) % grenadeAnimations.size();
		currentSprite = levelState->getSprite(grenadeAnimations[spriteIndex]);
		currentSprite.setScale(gameObject->getTransform()->getScale());
		gameObject->getComponent<SpriteComponent>()->setSprite(currentSprite);
	}
}


