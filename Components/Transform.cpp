#include "Transform.h"
#include <glm/gtc/matrix_transform.hpp>

Transform::Transform(GameObject* gameObject) : Component(gameObject)
{
	this->gameObject = gameObject;
	mat = glm::mat4(1.0f);
}

void Transform::Translate(glm::vec3& pos)
{
	position += pos;
	mat = glm::translate(glm::mat4(1.0f), position);
}

void Transform::Translate(glm::vec2& pos)
{
	position += glm::vec3(pos.x, pos.y, 0);
	mat = glm::translate(glm::mat4(1.0f), glm::vec3(position.x, position.y, position.z));
}

void Transform::Rotate(float& angle, glm::vec3& axis)
{
	mat = glm::rotate(mat, glm::radians(angle), axis);
	this->angle = angle;
	//Check which axis and add to rotation vector
	if (axis == glm::vec3(1.0f, 0.0f, 0.0f))
	{
		rotation.x = angle;
	}
	else if (axis == glm::vec3(0.0f, 1.0f, 0.0f))
	{
		rotation.y = angle;
	}
	else if (axis == glm::vec3(0.0f, 0.0f, 1.0f))
	{
		rotation.z = angle;
	}
}

void Transform::Scale(glm::vec3& scale)
{
	mat = glm::scale(mat, scale);

	//Check if scaling is not just the uniform
	if (scale.x != 1.0f)
	{
		this->scale.x = scale.x;
	}

	if (scale.y != 1.0f)
	{
		this->scale.y = scale.y;
	}

	if (scale.z != 1.0f)
	{
		this->scale.z = scale.z;
	}
}

void Transform::SetPos(glm::vec2 pos)
{
	position = glm::vec3(position.x, position.y, 0);
	mat = glm::translate(glm::mat4(1.0f), position);
}

void Transform::SetPos(glm::vec3 pos)
{
	position = pos;
	mat = glm::translate(glm::mat4(1.0f), position);
}

float Transform::getAngle() const
{
	return angle;
}

glm::vec3 Transform::getPos() const
{
	return position;
}

glm::vec3 Transform::getRot() const
{
	return rotation;
}

glm::vec3 Transform::getScale() const
{
	return scale;
}
