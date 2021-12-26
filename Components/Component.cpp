//
// Created by Morten Nobel-Jørgensen on 10/10/2017.
//

#include "Component.h"
#include "../Utility/Debug.h"

Component::Component(GameObject* gameObject)
	:gameObject(gameObject)
{
}

void Component::renderSprite(sre::SpriteBatch::SpriteBatchBuilder& spriteBatchBuilder)
{

}

void Component::update(float deltaTime)
{

}

bool Component::onKey(SDL_Event& event)
{
	return false;
}

void Component::onCollisionStart(PhysicsComponent* comp)
{

}

void Component::onCollisionEnd(PhysicsComponent* comp)
{

}


GameObject* Component::getGameObject()
{
	return gameObject;
}

void Component::setValuesFromJSON(rapidjson::GenericValue<rapidjson::UTF8<char>, rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>>* jsonObject)
{
	Debug::Log("setValuesFromJson should not call base function", Logs::WARNING);
}
