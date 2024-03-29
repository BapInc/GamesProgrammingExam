#ifndef COMPONENT_H
#define COMPONENT_H 
#include "sre/SpriteBatch.hpp"
#include "../rapidjson/document.h"

// Forward declaration
class GameObject;
class PhysicsComponent;

class Component {                                           // Abstract class that adds behavior to a GameObject
public:
	explicit Component(GameObject* gameObject);
	virtual ~Component() = default;

	GameObject* getGameObject();
	void setGameObject(GameObject* gameObject);
	virtual bool onKey(SDL_Event& event);                   // The function should return true, if the key event is consumed. This prevents other components to receive the event.

	virtual void update(float deltaTime);
	virtual void renderSprite(sre::SpriteBatch::SpriteBatchBuilder& spriteBatchBuilder);

	virtual void onCollisionStart(PhysicsComponent* comp);  // Callback from physics engine when collision start is detected. Override when needed.
	virtual void onCollisionEnd(PhysicsComponent* comp);    // Callback from physics engine when collision end is detected. Override when needed.
	virtual void setValuesFromJSON(rapidjson::GenericValue<rapidjson::UTF8<char>, rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>>* jsonObject);
protected:
	GameObject* gameObject;

	friend class GameObject;
};

#endif