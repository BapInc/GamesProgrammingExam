#include "GameObject.h"
#include <cassert>
#include <algorithm>
#include "../Components/Component.h"
#include "../Components/SpriteComponent.h"
#include "../AI/NavigationComponent.h"
#include "../Player/Player.h"
#include "../Components/WeaponComponent.h"
#include "../Components/BulletComponent.h"
#include "../Components/GranadeComponent.h"

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

std::string GameObject::getName()
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

GameObject* GameObject::clone(glm::vec2 pos, LevelState* state)
{
	auto cloneGO = new GameObject(*this);
	cloneGO->transform = transform->clone(cloneGO);
	cloneGO->transform->SetPos(pos);
	cloneGO->components.clear();

	for (auto& component : components) {
		auto sprite = std::dynamic_pointer_cast<SpriteComponent>(component);
		auto nav = std::dynamic_pointer_cast<NavigationComponent>(component);
		auto phys = std::dynamic_pointer_cast<PhysicsComponent>(component);
		auto player = std::dynamic_pointer_cast<Player>(component);
		auto weapon = std::dynamic_pointer_cast<WeaponComponent>(component);
		auto bullet = std::dynamic_pointer_cast<BulletComponent>(component);
		auto grenade = std::dynamic_pointer_cast<GranadeComponent>(component);

		if (sprite != nullptr) {
			auto spriteClone = std::shared_ptr<SpriteComponent>(sprite->clone(cloneGO));
			cloneGO->components.push_back(spriteClone);

			continue;
		}

		if (nav != nullptr) {
			cloneGO->components.push_back(std::shared_ptr<NavigationComponent>(nav->clone(cloneGO)));
			continue;
		}

		if (phys != nullptr) {
			auto physComp = std::shared_ptr<PhysicsComponent>(phys->clone(cloneGO, state->getPhysicsWorld()));
			cloneGO->components.push_back(physComp);

			continue;
		}
		if (player != nullptr) {
			auto playerClone = new Player(*player);
			playerClone->setLevel(*state);
			auto playerComponent = std::shared_ptr<Player>(new Player(*playerClone));
			cloneGO->components.push_back(playerComponent);
			continue;
		}
		if (weapon != nullptr) {
			auto weaponComponent = std::shared_ptr<WeaponComponent>(new WeaponComponent(*weapon));
			cloneGO->components.push_back(weaponComponent);
			continue;
		}
		if (bullet != nullptr) {
			auto bulletComponent = std::shared_ptr<BulletComponent>(new BulletComponent(*bullet));
			cloneGO->components.push_back(bulletComponent);
			continue;
		}
		if (grenade != nullptr) {
			auto grenadeComponent = std::shared_ptr<GranadeComponent>(new GranadeComponent(*grenade));
			cloneGO->components.push_back(grenadeComponent);
			continue;
		}

		// THIS DOESN'T WORK. Pushing back new Component(*component); pushes back a new gameobject and not component
	/*	else {
			cloneGO->components.push_back(std::shared_ptr<Component>(new Component(*component)));
		}*/
	}
	auto player = cloneGO->getComponent<Player>();
	if (player != nullptr) {
		player->setSpriteComponent(cloneGO->getComponent<SpriteComponent>());

	}
	for (auto& component : cloneGO->components) {
		component->setGameObject(cloneGO);
	}
	return cloneGO;
}

