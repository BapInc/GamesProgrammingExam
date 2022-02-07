//

#include <Box2D/Box2D.h>
#include <iostream>
#include "PhysicsComponent.h"
#include "../Game/DungeonGame.h"
#include "../GameStates/LevelState.h"

PhysicsComponent::PhysicsComponent(GameObject* gameObject)
	: Component(gameObject)
{
	this->gameObject = gameObject;
	//world = DungeonGame::getInstance()->world;
}


PhysicsComponent::~PhysicsComponent()
{
	//BirdGame::instance->deregisterPhysicsComponent(this);

	delete polygon;
	delete circle;
	if (body != nullptr && fixture != nullptr)
	{
		body->DestroyFixture(fixture);
		fixture = nullptr;
	}
	if (world != nullptr && body != nullptr)
	{
		world->DestroyBody(body);
		body = nullptr;
	}
}

void PhysicsComponent::addImpulse(glm::vec2 impulse)
{
	b2Vec2 iForceV{ impulse.x,impulse.y };
	body->ApplyLinearImpulse(iForceV, body->GetWorldCenter(), true);
}

void PhysicsComponent::addForce(glm::vec2 force)
{
	b2Vec2 forceV{ force.x,force.y };
	body->ApplyForce(forceV, body->GetWorldCenter(), true);
}

glm::vec2 PhysicsComponent::getLinearVelocity()
{
	b2Vec2 v = body->GetLinearVelocity();
	return { v.x,v.y };
}

void PhysicsComponent::setLinearVelocity(glm::vec2 velocity)
{
	b2Vec2 v{ velocity.x, velocity.y };
	if (velocity != glm::vec2(0, 0))
	{
		body->SetAwake(true);
	}
	body->SetLinearVelocity(v);
}

void PhysicsComponent::initCircle(b2BodyType type, float radius, glm::vec2 center, float density)
{
	assert(body == nullptr);
	// do init
	shapeType = b2Shape::Type::e_circle;
	b2BodyDef bd;
	bd.type = type;
	rbType = type;
	bd.position = b2Vec2(center.x, center.y);
	body = world->CreateBody(&bd);
	circle = new b2CircleShape();
	circle->m_radius = radius;
	b2FixtureDef fxD;
	fxD.shape = circle;
	fxD.density = density;
	fixture = body->CreateFixture(&fxD);

	//BirdGame::instance->registerPhysicsComponent(this);
}

void PhysicsComponent::initBox(b2BodyType type, glm::vec2 size, glm::vec2 center, float density)
{
	assert(body == nullptr);
	// do init
	shapeType = b2Shape::Type::e_polygon;
	b2BodyDef bd;
	bd.type = type;
	rbType = type;
	bd.position = b2Vec2(center.x, center.y);
	body = world->CreateBody(&bd);
	polygon = new b2PolygonShape();
	polygon->SetAsBox(size.x, size.y, { 0,0 }, 0);
	b2FixtureDef fxD;
	fxD.shape = polygon;
	fxD.density = density;
	fixture = body->CreateFixture(&fxD);

	//TODO: Register physics components
	//BirdGame::instance->registerPhysicsComponent(this);
}

bool PhysicsComponent::isSensor()
{
	return fixture->IsSensor();
}

void PhysicsComponent::setSensor(bool enabled)
{
	fixture->SetSensor(enabled);
}

void PhysicsComponent::setValuesFromJSON(GenericValue<UTF8<char>, MemoryPoolAllocator<CrtAllocator>>* value, b2World* world)
{
	this->world = world;

	glm::vec2 center = { 0,0 };
	center.x = value->operator[]("center").GetObject()["x"].GetFloat();
	center.y = value->operator[]("center").GetObject()["y"].GetFloat();

	std::string shape = value->operator[]("shape").GetString();
	std::string bodyType = value->operator[]("b2BodyType").GetString();


	float density = value->operator[]("density").GetFloat();

	if (shape == "box")
	{
		Debug::Log("Creating Box", Logs::WARNING);
		b2BodyType type;
		if (bodyType == "b2_dynamicBody")
		{
			type = b2BodyType::b2_dynamicBody;
		}
		else if (bodyType == "b2_kinematicBody")
		{
			type = b2BodyType::b2_kinematicBody;
		}
		else
		{
			type = b2BodyType::b2_staticBody;
		}

		glm::vec2 size = { 0,0 };
		size.x = value->operator[]("size").GetObject()["x"].GetFloat();
		size.y = value->operator[]("size").GetObject()["y"].GetFloat();

		initBox(type, size, center, density);
	}
	else if (shape == "circle")
	{
		Debug::Log("Creating circle", Logs::WARNING);
		b2BodyType type;
		if (bodyType == "b2_dynamicBody")
		{
			type = b2BodyType::b2_dynamicBody;
		}
		else if (bodyType == "b2_kinematicBody")
		{
			type = b2BodyType::b2_kinematicBody;
		}
		else
		{
			type = b2BodyType::b2_staticBody;
		}
		float radius = value->operator[]("radius").GetFloat();
		initCircle(type, radius, center, density);
	}
}

