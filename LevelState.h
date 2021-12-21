#ifndef LEVELSTATE_H
#define LEVELSTATE_H

#include "GameState.h"
#include "Box2DDebugDraw.hpp"
#include "sre/SpriteAtlas.hpp"
#include "PhysicsComponent.hpp"
#include "Box2D/Dynamics/b2World.h"
#include "TopDownCameraComponent.h"
#include "SpriteManager.hpp"

class PhysicsComponent;

class LevelState : public GameState, public b2ContactListener
{
public:

	LevelState();

	void start() override;
	void update() override;
	void render() override;

	void initPhysics();

	void BeginContact(b2Contact* contact) override;
	void EndContact(b2Contact* contact) override;

	void generateNewDungeon();

	void handleContact(b2Contact* contact, bool begin);
	std::shared_ptr<GameObject> LevelState::createGameObject();
private:

	const float physicsScale = 100;

	b2World* world = nullptr;
	std::shared_ptr<sre::SpriteAtlas> spriteAtlas;

	std::vector<std::shared_ptr<GameObject>> sceneObjects;
	std::map<b2Fixture*, PhysicsComponent*> physicsComponents;

	std::shared_ptr<TopDownCameraComponent> camera;

	Box2DDebugDraw debugDraw;
	bool doDebugDraw = false;

	void updatePhysics();
	void registerPhysicsComponent(PhysicsComponent* r);
	void deregisterPhysicsComponent(PhysicsComponent* r);
};

#endif;