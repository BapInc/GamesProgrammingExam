#include "Component.h"
#include "../Components/Component.h"
#include "../Game/GameObject.h"

class BulletComponent : public Component
{
public:
	explicit BulletComponent(GameObject* gameObject);

	void setBulletDirection(glm::vec2 mouseDirection);

	void update(float deltaTime) override;
	
private:

	glm::vec2 bulletDirection;
	float speed = 200.0f;
};
