#include "PlayState.h"
#include "DungeonGame.h"

#include "Box2D/Dynamics/Contacts/b2Contact.h"


PlayState::PlayState() :debugDraw(physicsScale)
{
}

void PlayState::start()
{
	//camera.reset();
	//sceneObjects.clear();
	//camera.reset();
	auto camObj = createGameObject();
	camObj->name = "Camera";
	camera = camObj->addComponent<TopDownCameraComponent>();
	camObj->setPosition(DungeonGame::instance()->getWindowSize() * 0.5f);
}

void PlayState::update()
{
}

void PlayState::render()
{
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

