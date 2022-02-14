#include "GameObject.h"
#include <cassert>
#include <algorithm>
#include "../Components/Component.h"
#include "../Components/SpriteComponent.h"
#include "../AI/NavigationComponent.h"

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

GameObject* GameObject::clone()
{
	auto cloneGO = new GameObject(*this);
	cloneGO->transform = transform->clone(cloneGO);
	cloneGO->components.clear();

	for (auto& component : components) {
		auto sprite = std::dynamic_pointer_cast<SpriteComponent>(component);
		if (sprite != nullptr) {

			cloneGO->components.push_back(std::shared_ptr<SpriteComponent>(sprite->clone(cloneGO)));
			continue;
		}

		auto nav = std::dynamic_pointer_cast<NavigationComponent>(component);
		if (nav != nullptr) {
			cloneGO->components.push_back(std::shared_ptr<NavigationComponent>(nav->clone(cloneGO)));
			continue;
		}

		auto phys = std::dynamic_pointer_cast<PhysicsComponent>(component);
		if (phys != nullptr) {

			cloneGO->components.push_back(std::shared_ptr<PhysicsComponent>(phys->clone(cloneGO)));
			continue;
		}
	}

	for (auto& component : cloneGO->components) {
		component->setGameObject(cloneGO);
	}
	return cloneGO;
}
