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

	this->radius = radius;

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

}

void PhysicsComponent::initBox(b2BodyType type, glm::vec2 size, glm::vec2 center, float density)
{
	assert(body == nullptr);

	width = size.x;
	height = size.y;

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
}


std::shared_ptr<PhysicsComponent> PhysicsComponent::clone(GameObject* gameObject, b2World* world)
{
	auto clone = std::make_shared<PhysicsComponent>(gameObject);

	clone->gameObject = gameObject;
	clone->setWorld(world);

	b2FixtureDef fxD;

	if (polygon != nullptr)
	{
		clone->polygon = new b2PolygonShape(*polygon);
		b2BlockAllocator* allocator = new b2BlockAllocator();
		allocator->Allocate(sizeof(polygon));

		clone->polygon = new b2PolygonShape(*polygon);
		fxD.shape = clone->polygon;
		clone->shapeType = b2Shape::Type::e_polygon;
	}
	else if (circle != nullptr) {
		clone->circle = new b2CircleShape(*circle);
		fxD.shape = clone->circle;
		clone->shapeType = b2Shape::Type::e_circle;
	}

	//clone->polygon = nullptr;

	b2BodyDef bd;
	bd.type = b2BodyType::b2_dynamicBody;
	bd.position = b2Vec2(clone->gameObject->getTransform()->getPos().x / LevelState::physicsScale, clone->gameObject->getTransform()->getPos().y / LevelState::physicsScale);

	clone->rbType = b2BodyType::b2_dynamicBody;
	clone->body = clone->world->CreateBody(&bd);
	//clone->circle = new b2CircleShape();
	//clone->circle->m_radius = 0.1f;
	clone->body->SetFixedRotation(true);
	fxD.density = 1;

	clone->fixture = clone->body->CreateFixture(&fxD);
	return clone;
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
		size.x = value->operator[]("size").GetObject()["x"].GetFloat() / 100;
		size.y = value->operator[]("size").GetObject()["y"].GetFloat() / 100;

		initBox(type, size, center, density);
	}
	else if (shape == "circle")
	{
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
		float radius = value->operator[]("radius").GetFloat() / 100;
		initCircle(type, radius, center, density);
	}

}

void PhysicsComponent::moveTo(glm::vec2 pos) {
	glm::vec2 delta = pos - gameObject->getTransform()->getPos();
	setLinearVelocity(delta * (1 / LevelState::timeStep));
}

void PhysicsComponent::setWorld(b2World* world) {
	this->world = world;
}


