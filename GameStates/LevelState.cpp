#include "LevelState.h"
#include "../Game/DungeonGame.h"
#include "../Components/SpriteComponent.h"
#include "../Components/AudioComponent.h"
#include "Box2D/Dynamics/Contacts/b2Contact.h"
#include "../Managers/PrefabManager.h"
#include "../Utility/Debug.h"


using namespace sre;

LevelState::LevelState() : debugDraw(physicsScale)
{
}

void LevelState::start()
{
	initPhysics();
	loadSpriteSheet("spritesheet.json", "spritesheet.png");
	dungeon = new NormalDungeon(*this);
	dungeon->generateDungeon();

	//CAMERA
	//
	//camera.reset();
	//sceneObjects.clear();
	//camera.reset();
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
	camAudio->playSound("music");

	//PREFABS
	auto prefabLoader = new PrefabManager();
	prefabLoader->loadGameObjectsFromFile("./GameObjects.json", this);

	//PLAYER
	player = prefabLoader->getPrefab("Player");
	createGameObject(player.get());
	player->getComponent<Player>()->setLevel(*this);
	player->transform->SetPos({ -200, 200 });
	player->getComponent<SpriteComponent>()->getSprite().setScale({ 2,2 });
	camera->setFollowObject(player);

#ifdef _DEBUG
	std::cout << "Camera instantiated" << std::endl;
#endif

	auto obj = createGameObject();
	obj->name = "Demon";
	auto spC = obj->addComponent<SpriteComponent>();
	auto sprit = getSprite("floor_1.png"); // spriteAtlas->get("floor_1.png");
	sprit.setScale({ 2,2 });
	spC->setSprite(sprit);
	obj->transform->SetPos({ -100,150 });

	//Player
	/*auto playerGO = createGameObject();
	playerGO->name = "Player";
	player = playerGO->addComponent<Player>();
	player->setLevel(*this);
	auto playerSprite = playerGO->addComponent<SpriteComponent>();
	auto pSprite = getSprite("lizard_f_idle_anim_f0.png");
	pSprite.setScale({ 2,2 });
	playerSprite->setSprite(pSprite);
	playerGO->transform->SetPos({ -200,200 });

	camera->setFollowObject(playerGO);
	//camera->setFollowObject(obj, { +150,DungeonGame::getInstance()->getWindowSize().y / 2 });*/

	dungeon->drawAsciiDungeon();
}

void LevelState::update(float deltaTime)
{
	for (auto& obj : sceneObjects)
	{
		obj->update(deltaTime);
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
		go->renderSprite(spriteBatchBuilder);
	}


	auto sb = spriteBatchBuilder.build();
	rp.draw(sb);


	if (doDebugDraw)
	{
		world->DrawDebugData();
		rp.drawLines(debugDraw.getLines());
		debugDraw.clear();
	}
}

void LevelState::onKey(SDL_Event& event)
{
	player->getComponent<Player>()->onKey(event);

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
	sceneObjects.push_back(obj);
	return obj;
}

std::shared_ptr<GameObject> LevelState::createGameObject(GameObject* object)
{
	auto obj = std::shared_ptr<GameObject>(object);
	sceneObjects.push_back(obj);
	return obj;
}

b2World* LevelState::getPhysicsWorld()
{
	return world;
}

