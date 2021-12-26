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

	std::string getTag() const;
	const std::vector<std::shared_ptr<Component>>& getComponents();
	Transform* getTransform();

private:

	bool shouldDestroy = false;

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