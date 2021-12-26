#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "Component.h"
#include <glm/matrix.hpp>
class Transform : public Component
{
public: 
	explicit Transform(GameObject* object);

public:

	void Translate(glm::vec3& pos);
	void Translate(glm::vec2& pos);
	void Rotate(float& angle, glm::vec3& axis);
	void Scale(glm::vec3& scale);

public:

	void SetPos(glm::vec2 pos);
	void SetPos(glm::vec3 pos);

public:

	float getAngle() const;
	glm::vec3 getPos() const;
	glm::vec3 getRot() const;
	glm::vec3 getScale() const;

private:

	float angle;

	glm::mat4 mat;
	glm::vec3 scale;
	glm::vec3 position;
	glm::vec3 rotation;
};
#endif // !TRANSFORM_H
