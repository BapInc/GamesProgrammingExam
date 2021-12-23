#ifndef LEVELSTATE_H
#define LEVELSTATE_H

#include "GameState.h"
#include "../Utility/Box2DDebugDraw.h"
#include "sre/SpriteAtlas.hpp"
#include "../Components/PhysicsComponent.h"
#include "Box2D/Dynamics/b2World.h"
#include "../Components/TopDownCameraComponent.h"
#include "../Dungeon/NormalDungeon.h"

class PhysicsComponent;

class LevelState : public GameState, public b2ContactListener
{
public:

	LevelState();

	void start() override;
	void update(float time) override;
	void render() override;
	void onKey() override;

	void initPhysics();

	void BeginContact(b2Contact* contact) override;
	void EndContact(b2Contact* contact) override;

	void generateNewDungeon();

	void handleContact(b2Contact* contact, bool begin);
	std::shared_ptr<GameObject> LevelState::createGameObject();
	std::shared_ptr<GameObject> LevelState::createGameObject(GameObject* object);
private:

	const float physicsScale = 100;

	b2World* world = nullptr;
	std::shared_ptr<sre::SpriteAtlas> spriteAtlas;

	std::vector<std::shared_ptr<GameObject>> sceneObjects;
	std::map<b2Fixture*, PhysicsComponent*> physicsComponents;

	std::shared_ptr<TopDownCameraComponent> camera;

	Box2DDebugDraw debugDraw;
	bool doDebugDraw = false;
	Dungeon* dungeon;

	void updatePhysics();
	void registerPhysicsComponent(PhysicsComponent* r);
	void deregisterPhysicsComponent(PhysicsComponent* r);
};

#endif;