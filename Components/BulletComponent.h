#include "Component.h"
#include "../Components/Component.h"
#include "../Game/GameObject.h"

class BulletComponent : public Component
{
public:
	explicit BulletComponent(GameObject* gameObject);

	void shoot(sre::Sprite bullet, glm::vec2 pos, glm::vec2 vel, float rot);
	void update(float deltaTime) override;
	
private:
	

};
