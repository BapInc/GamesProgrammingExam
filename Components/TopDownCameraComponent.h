#ifndef TOPDOWNCAMERACOMPONENT_H
#define TOPDOWNCAMERACOMPONENT_H

#include "Component.h"
#include "sre/Camera.hpp"
#include "glm/glm.hpp"

class TopDownCameraComponent : public Component
{
public:
	explicit TopDownCameraComponent(GameObject* gameObject);

	void update(float deltaTime) override;

	void setFollowObject(std::shared_ptr<GameObject> followObject);

	sre::Camera& getCamera();

private:
	glm::vec2 offset;
	sre::Camera camera;
	std::shared_ptr<GameObject> followObject;
};

#endif
