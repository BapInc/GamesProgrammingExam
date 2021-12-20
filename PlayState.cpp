#include "PlayState.h"
#include "DungeonGame.h"
#include "SpriteComponent.hpp"
#include "Box2D/Dynamics/Contacts/b2Contact.h"
#include "TileMap.hpp"

using namespace sre;

PlayState::PlayState() :debugDraw(physicsScale)
{
}
std::vector<std::vector<std::shared_ptr<Tile>>> tiles;
void PlayState::start()
{
	//camera.reset();
	//sceneObjects.clear();
	//camera.reset();
	auto camObj = createGameObject();
	camObj->name = "Camera";
	camera = camObj->addComponent<TopDownCameraComponent>();
	camObj->setPosition(DungeonGame::getInstance()->getWindowSize() * 0.5f);
#ifdef _DEBUG
	std::cout << "Camera instantiated" << std::endl;
#endif
	auto obj = createGameObject();
	obj->name = "Tile";
	auto spC = obj->addComponent<SpriteComponent>();
	auto sprit = SpriteManager::getInstance()->getSprite("big_demon_idle_anim_f0.png"); // spriteAtlas->get("floor_1.png");
	spC->setSprite(*sprit);
	obj->setPosition({ -100,150 });

	auto tilemap = new TileMap(50, 50, glm::vec2{ 0,0 } - DungeonGame::getInstance()->getWindowSize() * 0.4f);
	auto x = tilemap->getTiles();
	tiles = x;
	//camera->setFollowObject(obj, { +150,DungeonGame::getInstance()->getWindowSize().y / 2 });
}

void PlayState::update()
{

}

void PlayState::render()
{
	auto rp = RenderPass::create()
		.withCamera(camera->getCamera())
		.build();

	auto pos = camera->getGameObject()->getPosition();
	auto spriteBatchBuilder = SpriteBatch::create();
	for (auto& sprite : tiles)
	{
		for (auto& sprite2 : sprite)
		{

			spriteBatchBuilder.addSprite(sprite2->getSprite());

		}
	}
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

void PlayState::initPhysics()
{
	delete world;
	world = new b2World(b2Vec2(0, 0));
	world->SetContactListener(this);

	if (doDebugDraw)
	{
		world->SetDebugDraw(&debugDraw);
	}
}

void PlayState::BeginContact(b2Contact* contact)
{
	b2ContactListener::BeginContact(contact);
	handleContact(contact, true);
}

void PlayState::EndContact(b2Contact* contact)
{
	b2ContactListener::EndContact(contact);
	handleContact(contact, false);
}

void PlayState::generateNewDungeon()
{
}

void PlayState::handleContact(b2Contact* contact, bool begin)
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

std::shared_ptr<GameObject> PlayState::createGameObject()
{
	auto obj = std::shared_ptr<GameObject>(new GameObject());
	sceneObjects.push_back(obj);
	return obj;
}

