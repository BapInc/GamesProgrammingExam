#include "GameObject.h"
#include <cassert>
#include <algorithm>
#include "../Components/Component.h"

GameObject::~GameObject()
{
	// remove reference to this in components
	for (auto& c : components)
	{
		c->gameObject = nullptr;
	}
	delete(transform);
	transform = nullptr;
}

GameObject::GameObject()
{
	transform = new Transform(this);
}

bool GameObject::removeComponent(std::shared_ptr<Component> component)
{
	auto comp = std::find(components.begin(), components.end(), component);
	if (comp != components.end())
	{
		components.erase(comp);
	}
	return false;
}

std::string GameObject::getTag() const
{
	return tag;
}

std::string GameObject::getName() const
{
	return name;
}

void GameObject::renderSprite(sre::SpriteBatch::SpriteBatchBuilder& spriteBatchBuilder)
{
	for (auto& comp : components)
	{
		comp->renderSprite(spriteBatchBuilder);
	}
}

void GameObject::update(float deltaTime)
{
	for (auto& comp : components)
	{
		comp->update(deltaTime);
	}
}

bool GameObject::getActive() {
	return isActive;
}

void GameObject::setActive(bool setActive)
{
	isActive = setActive;
}

void GameObject::setName(std::string& name)
{
	this->name = name;
}

const std::vector<std::shared_ptr<Component>>& GameObject::getComponents()
{
	return components;
}

Transform* GameObject::getTransform()
{
	return transform;
}
