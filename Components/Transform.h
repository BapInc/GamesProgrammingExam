#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "Component.h"
#include <glm/matrix.hpp>
class Transform : public Component
{
public:
	explicit Transform(GameObject* object);

public:

	void SetIdentity();

	void Translate(glm::vec2& pos);
	void Translate(float& x, float& y);
	void Rotate(float& angle);
	void Scale(glm::vec3& scale);

public:

	void SetPos(glm::vec2 pos);
	void SetRot(glm::vec3 rot);
	void SetScale(glm::vec3 scale);

public:

	float getAngle() const;
	glm::vec2 getPos() const;
	glm::vec3 getRot() const;
	glm::vec3 getScale() const;

private:

	float angle;

	//glm::mat4 mat;
	glm::vec3 scale = { 1,1,1 };
	glm::vec2 position = { 0,0 };
	glm::vec3 rotation = { 0,0,0 };

public:
	Transform* clone(GameObject* gameObject);
};
#endif // !TRANSFORM_H
