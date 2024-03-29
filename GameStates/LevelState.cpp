#include "LevelState.h"
#include "../Game/DungeonGame.h"
#include "../Components/SpriteComponent.h"
#include "../Components/AudioComponent.h"
#include "../Components/WeaponComponent.h"
#include "Box2D/Dynamics/Contacts/b2Contact.h"
#include "../Utility/Debug.h"
#include "../AI/NavigationComponent.h"

using namespace sre;

LevelState::LevelState() : debugDraw(physicsScale)
{
	std::cout << "Level";
}

void LevelState::start()
{
	initPhysics();
	loadSpriteSheet("spritesheet.json", "spritesheet.png");

	auto camObj = createGameObject();
	camObj->name = "Camera";
	camera = camObj->addComponent<TopDownCameraComponent>();
	camObj->getTransform()->SetPos(DungeonGame::getInstance()->getWindowSize() * 0.5f);

	//AUDIO
	// ======== EXAMPLE =================
	// || Add Component and play audio ||
	// ======== EXAMPLE =================
	auto camAudio = camObj->addComponent<AudioComponent>();
	camAudio->addSound("music", "event:/BackgroundMusic");
	camAudio->addSound("shoot", "event:/Shot");
	camAudio->addSound("explosion", "event:/Explosion");
	camAudio->addSound("run", "event:/Run");
	camAudio->playSound("music");
	prefabManager = std::make_shared<PrefabManager>();
	prefabManager->loadGameObjectsFromFile("./GameObjects.json", this);

	dungeon = new NormalDungeon(*this);
	dungeon->generateDungeon();
	//PLAYER
	player = loadPrefab("Player", dungeon->getStartRoomPos());
	player->getComponent<Player>()->setLevel(*this);
	player->getComponent<Player>()->setAudio(*camAudio);
	camera->setFollowObject(player);
	player->getComponent<Player>()->start();
	player->transform->SetPos(dungeon->getStartRoomPos());


#ifdef _DEBUG
	std::cout << "Camera instantiated" << std::endl;
#endif

	dungeon->drawAsciiDungeon();

	//prefabManager->clearPrefabs();
	Debug::Log(std::to_string(player->transform->getPos().x) + " " + std::to_string(player->transform->getPos().y));
	Debug::Log(std::to_string(dungeon->getStartRoomPos().x) + " " + std::to_string(dungeon->getStartRoomPos().y));

}

std::shared_ptr<GameObject> LevelState::loadPrefab(std::string prefab, glm::vec2 pos) {
	return prefabManager->getPrefab(prefab, this, pos);
}

void LevelState::update(float deltaTime)
{
	
	updatePhysics();

	if (player->getActive() == false)
		return;

	for (auto& obj : sceneObjects)
	{
		if (obj->getActive()) {
			obj->update(deltaTime);
		}
	}

	for (int i = 0; i < sceneObjects.size(); i++) {
		if (sceneObjects[i]->getShouldDestroy()) {
			auto physicsComponent = sceneObjects[i]->getComponent<PhysicsComponent>();
			physicsComponents.erase(physicsComponent->fixture);
			sceneObjects.erase(sceneObjects.begin() + i);
		}
	}
}

void LevelState::render()
{
	auto rp = RenderPass::create()
		.withCamera(camera->getCamera())
		.build();

	auto pos = camera->getGameObject()->getTransform()->getPos();

	auto spriteBatchBuilder = SpriteBatch::create();
	for (auto& go : sceneObjects)
	{
		if (go->getActive()) {
			go->renderSprite(spriteBatchBuilder);
		}
	}


	auto sb = spriteBatchBuilder.build();
	rp.draw(sb);


	if (doDebugDraw)
	{
		world->DrawDebugData();
		rp.drawLines(debugDraw.getLines());
		debugDraw.clear();
	}

	ImGui::SetNextWindowPos(ImVec2(Renderer::instance->getWindowSize().x / 2 - 100, .0f), ImGuiSetCond_Always);
	ImGui::SetNextWindowSize(ImVec2(400, 100), ImGuiSetCond_Always);
	ImGui::Begin("Player");
	//ImGui::Text("Player pos: x: %02d, y: %02d", enemyPos.x, enemyPos.y);
	auto goCount = "Scene objects: " + std::to_string(sceneObjects.size());
	ImGui::Text(goCount.c_str());
	auto playerHealth = "Player Health: " + std::to_string(player->getComponent<Player>()->getHealth());
	ImGui::Text(playerHealth.c_str());
	ImGui::End();
}

void LevelState::onKey(SDL_Event& event)
{
	if(player->getActive())
		player->getComponent<Player>()->onKey(event);

	if (event.type == SDL_KEYDOWN)
	{
		switch (event.key.keysym.sym)
		{

		case SDLK_p:
			// press 'd' for physics debug
			doDebugDraw = !doDebugDraw;
			if (doDebugDraw)
			{
				world->SetDebugDraw(&debugDraw);
			}
			else
			{
				world->SetDebugDraw(nullptr);
			}
			break;
		case SDLK_r:

			if (player->getActive() == false)
			{
				restart();
			}
			break;
		}
	}

}

void LevelState::initPhysics()
{
	delete world;
	world = new b2World(b2Vec2(0, 0));
	world->SetContactListener(this);

	if (doDebugDraw)
	{
		world->SetDebugDraw(&debugDraw);
	}
}

void LevelState::restart()
{
	player->setActive(true);
	player->getComponent<PhysicsComponent>()->setPos(dungeon->getStartRoomPos());
	player->transform->SetPos(dungeon->getStartRoomPos());
	player->getComponent<Player>()->activateWeapon(true);
	//player->getComponent<Player>()->activate(true);
	//player->getComponent<Player>()->restart(dungeon->getStartRoomPos());
}

void LevelState::updatePhysics()
{
	const float32 timeStep = 1.0f / 60.0f;
	const int positionIterations = 2;
	const int velocityIterations = 6;
	world->Step(timeStep, velocityIterations, positionIterations);

	for (auto phys : physicsComponents)
	{
		if (phys.second->rbType == b2_staticBody) continue;
		auto position = phys.second->body->GetPosition();
		float angle = phys.second->body->GetAngle();
		auto gameObject = phys.second->getGameObject();

		if (gameObject->isActive == true)
		{
			gameObject->getTransform()->SetPos(glm::vec2(position.x * physicsScale, position.y * physicsScale));
			gameObject->getTransform()->Rotate(angle);
		}
	}
}

void LevelState::BeginContact(b2Contact* contact)
{
	b2ContactListener::BeginContact(contact);
	handleContact(contact, true);
}

void LevelState::EndContact(b2Contact* contact)
{
	b2ContactListener::EndContact(contact);
	handleContact(contact, false);
}

void LevelState::generateEnemy(glm::ivec2& pos)
{
	auto enemy = prefabManager->getPrefab("Enemy", this, pos);
	auto nav = enemy->getComponent<NavigationComponent>();
	nav->setLevel(*this);
	nav->activateNavigation();
}

void LevelState::handleContact(b2Contact* contact, bool begin)
{
	auto fixA = contact->GetFixtureA();
	auto fixB = contact->GetFixtureB();
	auto physA = physicsComponents.find(fixA);
	auto physB = physicsComponents.find(fixB);
	if (physA != physicsComponents.end() && physB != physicsComponents.end())
	{
		auto& aComponents = physA->second->getGameObject()->getComponents();
		auto& bComponents = physB->second->getGameObject()->getComponents();
		for (auto& c : aComponents)
		{
			if (begin)
			{
				c->onCollisionStart(physB->second);
			}
			else
			{
				c->onCollisionEnd(physB->second);
			}
		}
		for (auto& c : bComponents)
		{
			if (begin)
			{
				c->onCollisionStart(physA->second);
			}
			else
			{
				c->onCollisionEnd(physA->second);
			}
		}
	}
}

std::shared_ptr<GameObject> LevelState::createGameObject()
{
	auto obj = std::shared_ptr<GameObject>(new GameObject());
	auto physicsComponent = obj->getComponent<PhysicsComponent>();
	if (physicsComponent != nullptr) {
		physicsComponents[physicsComponent->fixture] = physicsComponent.get();
	}
	sceneObjects.push_back(obj);
	return obj;
}

void LevelState::addPhysicsComponent(std::shared_ptr<PhysicsComponent>& pc)
{
	physicsComponents[pc.get()->fixture] = pc.get();
}

std::shared_ptr<GameObject> LevelState::createGameObject(GameObject* object)
{
	auto obj = std::shared_ptr<GameObject>(object);
	obj->setActive(true);
	auto physicsComponent = obj->getComponent<PhysicsComponent>();
	if (physicsComponent != nullptr) {
		physicsComponents[physicsComponent->fixture] = physicsComponent.get();
	}
	sceneObjects.push_back(obj);
	return obj;
}

std::shared_ptr<GameObject> LevelState::createGameObject(std::shared_ptr<GameObject> object)
{
	auto physicsComponent = object->getComponent<PhysicsComponent>();
	if (physicsComponent != nullptr) {
		physicsComponents[physicsComponent->fixture] = physicsComponent.get();
	}
	sceneObjects.push_back(object);
	return object;
}

b2World* LevelState::getPhysicsWorld()
{
	return world;
}

