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
	dungeon = new NormalDungeon(*this);
	dungeon->generateDungeon();

	auto camObj = createGameObject();
	camObj->name = "Camera";
	camera = camObj->addComponent<TopDownCameraComponent>();
	camObj->getTransform()->SetPos(DungeonGame::getInstance()->getWindowSize() * 0.5f);

	//AUDIO
	// ======== EXAMPLE =================
	// || Add Component and play audio ||
	// ======== EXAMPLE =================
	auto camAudio = camObj->addComponent<AudioComponent>();
	camAudio->addSound("music", "event:/music/music_main_menu00");
	//camAudio->playSound("music");
	prefabManager = std::make_shared<PrefabManager>();
	prefabManager->loadGameObjectsFromFile("./GameObjects.json", this);

	//PLAYER
	player = loadPrefab("Player", dungeon->getStartRoomPos());
	player->getComponent<Player>()->setLevel(*this);
	camera->setFollowObject(player);
	player->getComponent<Player>()->addWeapon();
	player->transform->SetPos(dungeon->getStartRoomPos());

	//player->transform->SetPos(dungeon->getStartRoomPos());

	// ======== EXAMPLE =================
	// ||		   AI				   ||
	// ======== EXAMPLE =================
	/*for (int i = 0; i < 4; i++) {

		// Set pos does nothing because of the way physicscomponents are instantiated
		auto enemyPos = glm::vec2((dungeon->getStartRoomPos().x + ((i + 10) * i)), dungeon->getStartRoomPos().y);
		//auto enemyPos = glm::vec2(-200 /, 200);
		auto enemy = prefabManager->getPrefab("Enemy", this, enemyPos);
		auto enemyGO = createGameObject(enemy.get());
		auto nav = enemyGO->getComponent<NavigationComponent>();
		nav->activateNavigation();
	}*/


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
	ImGui::End();
}

void LevelState::onKey(SDL_Event& event)
{
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
		gameObject->getTransform()->SetPos(glm::vec2(position.x * physicsScale, position.y * physicsScale));
		gameObject->getTransform()->Rotate(angle);
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

void LevelState::generateNewDungeon()
{
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

