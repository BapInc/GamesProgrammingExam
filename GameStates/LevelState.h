#ifndef LEVELSTATE_H
#define LEVELSTATE_H

#include "GameState.h"
#include "sre/SpriteAtlas.hpp"
#include "Box2D/Dynamics/b2World.h"

#include "../Player/Player.h"
#include "../Dungeon/NormalDungeon.h"
#include "../Utility/Box2DDebugDraw.h"
#include "../Managers/PrefabManager.h"
#include "../Components/PhysicsComponent.h"
#include "../Components/TopDownCameraComponent.h"
#include "../Player/Player.h"


class PhysicsComponent;
class Player;
class PrefabManager;

class LevelState : public GameState, public b2ContactListener
{
public:

	LevelState();

	void start() override;
	void update(float time) override;
	void render() override;
	void onKey(SDL_Event& event) override;

	void initPhysics();

	void BeginContact(b2Contact* contact) override;
	void EndContact(b2Contact* contact) override;
	std::shared_ptr<GameObject> loadPrefab(std::string prefab);
	void generateNewDungeon();

	void handleContact(b2Contact* contact, bool begin);
	std::shared_ptr<GameObject> LevelState::createGameObject();
	std::shared_ptr<GameObject> LevelState::createGameObject(GameObject* object);
	std::shared_ptr<GameObject> LevelState::createGameObject(std::shared_ptr<GameObject> object);
	b2World* getPhysicsWorld();
private:

	const float physicsScale = 100;

	b2World* world = nullptr;
	std::shared_ptr<sre::SpriteAtlas> spriteAtlas;
	std::shared_ptr<PrefabManager> prefabManager;

	std::vector<std::shared_ptr<GameObject>> sceneObjects;
	std::map<b2Fixture*, PhysicsComponent*> physicsComponents;

	std::shared_ptr<TopDownCameraComponent> camera;
	std::shared_ptr<GameObject> player;

	PrefabManager* prefabLoader;

	Box2DDebugDraw debugDraw;
	bool doDebugDraw = false;
	Dungeon* dungeon;

	//PrefabManager* prefabLoader;

	void updatePhysics();
	void registerPhysicsComponent(PhysicsComponent* r);
	void deregisterPhysicsComponent(PhysicsComponent* r);
};

#endif;