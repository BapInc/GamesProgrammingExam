#include "Transform.h"
#include <glm/gtc/matrix_transform.hpp>

Transform::Transform(GameObject& object)
{
	gameObject = object;
}

void Transform::Translate(glm::vec3& pos)
{
	mat = glm::translate(mat, pos);

	//Add to Local Pos
	position += pos;
}

void Transform::Rotate(float& angle, glm::vec3& axis)
{
	mat = glm::rotate(mat, glm::radians(angle), axis);

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
