#include "PrefabManager.h"
#include "../Utility/FileLoader.h"
#include "../Utility/Debug.h"
#include "../Components/AudioComponent.h"
#include "../Components/SpriteAnimationComponent.h"
#include "../Components/PhysicsComponent.h"
#include "../AI/NavigationComponent.h"
#include "../Components/WeaponComponent.h"


void PrefabManager::loadGameObjectsFromFile(std::string path, LevelState* state)
{
	auto document = FileLoader::loadJSONDocument(path);
	// Iterate through gameobjects
	for (auto& go : document->GetArray()) {

		std::shared_ptr<GameObject> gameObject = std::make_shared<GameObject>();
		std::string name = go["name"].GetString();
		gameObject->setName(name);

		if (go.HasMember("transform"))
		{
			auto transformJson = go["transform"].GetObject();
			auto transform = gameObject->getTransform();

			auto jsonScale = transformJson["scale"].GetObject();
			glm::vec3 scale;
			scale.x = jsonScale["x"].GetFloat();
			scale.y = jsonScale["y"].GetFloat();
			scale.z = jsonScale["z"].GetFloat();

			auto jsonRotation = transformJson["rotation"].GetObject();
			glm::vec3 rotation;
			rotation.x = jsonRotation["x"].GetFloat();
			rotation.y = jsonRotation["y"].GetFloat();
			rotation.z = jsonRotation["z"].GetFloat();

			auto jsonPosition = transformJson["position"].GetObject();
			glm::vec2 position;
			position.x = jsonPosition["x"].GetFloat();
			position.y = jsonPosition["y"].GetFloat();

			transform->SetPos(position);
			transform->SetRot(rotation);
			transform->SetScale(scale);
		}

		addComponents(go, gameObject, state);
		prefabs[name] = gameObject;
	}
}

void PrefabManager::addComponents(rapidjson::Value& go, std::shared_ptr<GameObject>& gameObject, LevelState* state)
{
	// Iterate through components on GameObject
	for (auto& component : go["components"].GetObject())
	{
		auto componentName = std::string(component.name.GetString());

		if (componentName == "AudioComponent")
		{
			auto audioComponent = gameObject->addComponent<AudioComponent>();
			audioComponent->setValuesFromJSON(&component.value);
		}
		else if (componentName == "PhysicsComponent")
		{
			auto physicsComponent = gameObject->addComponent<PhysicsComponent>();
			physicsComponent->setValuesFromJSON(&component.value, state->getPhysicsWorld());

		}
		else if (componentName == "SpriteAnimationComponent")
		{
			Debug::Log("Adding SpriteAnimationComponent");
			auto spriteAnimationComponent = gameObject->addComponent<SpriteAnimationComponent>();

		}
		else if (componentName == "SpriteComponent")
		{
			Debug::Log("Adding SpriteComponent");
			auto spriteComponent = gameObject->addComponent<SpriteComponent>();
			spriteComponent->setValuesFromJSON(&component.value, state);
		}
		else if (componentName == "TopDownCameraComponent")
		{
			Debug::Log("Adding TopDownCameraComponent");
			auto topDownCameraComponent = gameObject->addComponent<TopDownCameraComponent>();

		}
		else if (componentName == "Player") {
			auto playerComponent = gameObject->addComponent<Player>();
			playerComponent->setValuesFromJSON(&component.value, state);
		}
		else if (componentName == "WeaponComponent") {
			auto weaponComponent = gameObject->addComponent<WeaponComponent>();
		}
		else if (componentName == "NavigationComponent")
		{
			Debug::Log("Adding NavigationComponent");
			auto navigationComponent = gameObject->addComponent<NavigationComponent>();
			navigationComponent->setValuesFromJSON(&component.value);
		}

		Debug::Log("Loading component: " + std::string(componentName));
	}
}

std::shared_ptr<GameObject> PrefabManager::getPrefab(std::string name, LevelState* state, glm::vec2 pos, b2World* world)
{
	auto foundPrefab = prefabs[name];
	auto clone = foundPrefab->clone(pos, world);
	return state->createGameObject(clone);
}

void PrefabManager::clearPrefabs()
{
	prefabs.clear();
}
