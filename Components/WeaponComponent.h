#ifndef WEAPONCOMPONENT_H
#define WEAPONCOMPONENT_H

#include "Component.h"
#include "../Components/Component.h"
#include "../Game/GameObject.h"
#include "../Components/SpriteComponent.h"
#include "glm/glm.hpp"

class WeaponComponent : public Component 
{
public:
	explicit WeaponComponent(GameObject* gameObject);
	
	void setPlayer(GameObject& player);
	void setLevel(LevelState& levelState);
	bool flipWeapon();
	void update(float deltaTime) override;
	void setValuesFromJSON(GenericValue<UTF8<char>, MemoryPoolAllocator<CrtAllocator>>* value, GameState* state);
	std::shared_ptr<GameObject> getBulletType();
	void rotateWeapon();

private:
	GameObject* player;
	LevelState* levelState;
	std::string bullet;
	std::shared_ptr<GameObject> bulletType;
	int originX, originY;
	int x , y;
	float angle, radians;
};
#endif