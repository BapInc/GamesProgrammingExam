//
// Created by Morten Nobel-Jørgensen on 10/10/2017.
//

#include "SpriteComponent.h"
#include "../Game/GameObject.h"
#include "../Utility/Debug.h"
#include <iostream>
SpriteComponent::SpriteComponent(GameObject* gameObject) : Component(gameObject)
{
	this->gameObject = gameObject;
}

void SpriteComponent::renderSprite(sre::SpriteBatch::SpriteBatchBuilder& spriteBatchBuilder)
{
	sprite.setPosition(gameObject->getTransform()->getPos());
	sprite.setRotation(gameObject->getTransform()->getAngle());
	spriteBatchBuilder.addSprite(sprite);
}

void SpriteComponent::setSprite(const sre::Sprite& sprite)
{
	this->sprite = sprite;
}

sre::Sprite SpriteComponent::getSprite()
{
	return sprite;
}

void SpriteComponent::setValuesFromJSON(GenericValue<UTF8<char>, MemoryPoolAllocator<CrtAllocator>>* value, GameState* state)
{
	const char* img = value->operator[]("sprite").GetString();
	auto sprite = state->getSprite((char*)img);
	auto scale = value->operator[]("scale").GetObject();
	sprite.setScale({ scale["x"].GetFloat(), scale["y"].GetFloat() });
	setSprite(sprite);
}

void SpriteComponent::flipSprite(bool flip) {
	sprite.setFlip({ flip, false });
}

std::shared_ptr<SpriteComponent> SpriteComponent::clone(GameObject* gameObject)
{
	auto clone = std::shared_ptr<SpriteComponent>(new SpriteComponent(*this));
	clone->gameObject = gameObject;
	return clone;
}
