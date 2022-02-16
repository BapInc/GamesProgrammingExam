#include "TopDownCameraComponent.h"
#include "../Game/DungeonGame.h"

TopDownCameraComponent::TopDownCameraComponent(GameObject* gameObject) : Component(gameObject)
{
	this->gameObject = gameObject;
	camera.setOrthographicProjection(DungeonGame::getInstance()->getWindowSize().y / 2, -1, 1);
}

//TODO: This should have a is dirty flag to only update if needed
void TopDownCameraComponent::update(float deltaTime)
{
	if (followObject != nullptr)
	{
		//get position of PlayerGO
		glm::vec2 position = followObject->getTransform()->getPos();
		//Set position of PlayerGO to the camera game object
		gameObject->getTransform()->SetPos(position);
		//eye -> defines the position of the camera
		glm::vec3 eye(position, 0);
		//at -> the position where the camera is looking at (-1 is down)
		glm::vec3 at(position, -1);
		//up -> specifies the up direction of the camera
		glm::vec3 up(0, 1, 0);
		camera.lookAt(eye, at, up);
	}
}

void TopDownCameraComponent::setFollowObject(std::shared_ptr<GameObject> followObject)
{
	this->followObject = followObject;
}

sre::Camera& TopDownCameraComponent::getCamera()
{
	return camera;
}
