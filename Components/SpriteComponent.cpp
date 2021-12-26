//
// Created by Morten Nobel-Jørgensen on 10/10/2017.
//

#include "SpriteComponent.h"
#include "../Game/GameObject.h"

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
