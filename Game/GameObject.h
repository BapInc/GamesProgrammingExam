#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <memory>
#include <vector>
#include "glm/glm.hpp"
#include "sre/SpriteBatch.hpp"
#include "../Components/Transform.h"

// Forward declaration
class Component;
class Transform;
class LevelState;

// GameObject are empty container objects, which contains Components
class GameObject
{

public:

	~GameObject();
	GameObject();

public:

	template <class T>
	std::shared_ptr<T> addComponent();

	template <class T>
	std::shared_ptr<T> getComponent();

	bool removeComponent(std::shared_ptr<Component> component);

public:

	void renderSprite(sre::SpriteBatch::SpriteBatchBuilder& spriteBatchBuilder);
	void update(float deltaTime);
	bool getShouldDestroy();
	void setShouldDestroy(bool destroy);
	void setName(std::string& name);
	bool getActive();
	void setActive(bool setActive);
	std::string getTag() const;
	std::string setTag(std::string tag) const;
	std::string getName();
	const std::vector<std::shared_ptr<Component>>& getComponents();
	Transform* getTransform();
	GameObject* clone(glm::vec2 pos, LevelState* state);

private:

	bool shouldDestroy = false;
	bool isActive;

	Transform* transform;

	std::string tag = "";
	std::string name = "_";

	std::vector<std::shared_ptr<Component>> components;

	friend class LevelState;
};

// definition of the template member function addComponent
// Usage:
// GameObject* go = something;
// shared_ptr<SpriteComponent> sc = go->addComponent<SpriteComponent>();
template <class T>
inline std::shared_ptr<T> GameObject::addComponent()
{
	auto obj = std::shared_ptr<T>(new T(this));
	components.push_back(obj);

	return obj;
}

// definition of the template member function addComponent
// Usage:
// GameObject* go = something;
// shared_ptr<SpriteComponent> sc = go->addComponent<SpriteComponent>();
template <class T>
inline std::shared_ptr<T> GameObject::getComponent()
{
	for (auto c : components)
	{
		std::shared_ptr<T> res = std::dynamic_pointer_cast<T>(c);
		if (res != nullptr)
		{
			return res;
		}
	}
	return std::shared_ptr<T>();
}

#endif