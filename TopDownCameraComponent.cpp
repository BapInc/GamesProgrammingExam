#include "TopDownCameraComponent.h"
#include "DungeonGame.h"

TopDownCameraComponent::TopDownCameraComponent(GameObject* gameObject) : Component(gameObject)
{
	camera.setOrthographicProjection(DungeonGame::getInstance()->getWindowSize().y / 2, -1, 1);
}

//TODO: This should have a is dirty flag to only update if needed
void TopDownCameraComponent::update(float deltaTime)
{
	if (followObject != nullptr)
	{
		glm::vec2 position = followObject->getPosition();

		position.x += offset.x;
		position.y = offset.y;

		gameObject->setPosition(position);
		glm::vec3 eye(position, 0);
		glm::vec3 at(position, -1);
		glm::vec3 up(0, 1, 0);
		camera.lookAt(eye, at, up);
	}
}

void TopDownCameraComponent::setFollowObject(std::shared_ptr<GameObject> followObject, glm::vec2 offset)
{
	this->followObject = followObject;
	this->offset = offset;
}

sre::Camera& TopDownCameraComponent::getCamera()
{
	return camera;
}
