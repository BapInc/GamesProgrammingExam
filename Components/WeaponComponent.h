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
	
	void setPlayer(std::shared_ptr<GameObject> player);

	void update(float deltaTime) override;
	void setValuesFromJSON(GenericValue<UTF8<char>, MemoryPoolAllocator<CrtAllocator>>* value, GameState* state);

private:
	std::shared_ptr<GameObject> player;


};
#endif