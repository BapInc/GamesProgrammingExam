#ifndef BULLETCOMPONENT_H
#define BULLETCOMPONENT_H

#include "Component.h"
#include "../Components/Component.h"
#include "../Components/AudioComponent.h"
#include "../Game/GameObject.h"

class BulletComponent : public Component
{
public:
	explicit BulletComponent(GameObject* gameObject);

	void setBulletDirection(glm::vec2 mouseDirection);

	void update(float deltaTime) override;

	void setLevel(LevelState& levelState);

	void setAudio(AudioComponent& audio);

	virtual void shoot(float deltaTime);

	void onCollisionStart(PhysicsComponent* comp) override;
	
	LevelState* levelState;
	AudioComponent* audio;
	glm::vec2 bulletDirection;
	float speed;
	int lifetime;

private:

	std::shared_ptr<PhysicsComponent> physicsComponent;
};
#endif