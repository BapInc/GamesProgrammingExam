#ifndef PHYSICSCOMPONENT_H
#define PHYSICSCOMPONENT_H
#include "Box2D/Common/b2Math.h"
#include "Box2D/Collision/Shapes/b2PolygonShape.h"
#include "Box2D/Collision/Shapes/b2CircleShape.h"
#include "Box2D/Dynamics/b2Body.h"
#include "Component.h"
using namespace rapidjson;

class PhysicsComponent : public Component
{
public:
	explicit PhysicsComponent(GameObject* gameObject);
	virtual ~PhysicsComponent();
	void initCircle(b2BodyType type, float radius, glm::vec2 center, float density);
	void initBox(b2BodyType type, glm::vec2 size, glm::vec2 center, float density);

	void addForce(glm::vec2 force);     // Force gradually affects the velocity over time

	void addImpulse(glm::vec2 impulse);   // Instantly affects velocity

	void setLinearVelocity(glm::vec2 velocity);
	void PhysicsComponent::moveTo(glm::vec2 pos);

	glm::vec2 getLinearVelocity();

	bool isSensor();

	void setSensor(bool enabled);

	void setValuesFromJSON(GenericValue<UTF8<char>, MemoryPoolAllocator<CrtAllocator>>* value, b2World* world);
	void setWorld(b2World* world);
	std::shared_ptr<PhysicsComponent> clone(GameObject* gameObject, b2World* world);
	void setPos(glm::vec2 pos);
private:
	b2PolygonShape* polygon = nullptr;
	b2CircleShape* circle = nullptr;
	b2Body* body = nullptr;
	b2Shape::Type shapeType;
	b2Fixture* fixture = nullptr;
	b2BodyType rbType;
	std::vector<PhysicsComponent*> collidingBodies;
	b2World* world = nullptr;
	float radius = 1.0f;
	float height = 1.0f;
	float width = 1.0f;
	friend class LevelState;


};

#endif