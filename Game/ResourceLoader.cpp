#include "ResourceLoader.h"
#include "../Utility/FileLoader.h"
#include "../Utility/Debug.h"
#include "../Components/AudioComponent.h"
#include "../Components/SpriteAnimationComponent.h"

void ResourceLoader::loadGameObjectsFromFile(std::string path, LevelState* state)
{
	auto document = FileLoader::loadJSONDocument(path);
	// Iterate through gameobjects
	for (auto& go : document->GetArray()) {

		auto gameObject = state->createGameObject();
		gameObject->name = go["name"].GetString();
		// Iterate through componentss
		addComponents(go, gameObject, state);
	}
}

void ResourceLoader::addComponents(rapidjson::Value& go, std::shared_ptr<GameObject>& gameObject, LevelState* state)
{
	for (auto& component : go["components"].GetObject())
	{
		auto componentName = std::string(component.name.GetString());

		if (componentName == "AudioComponent")
		{
			auto audioComponent = gameObject->addComponent<AudioComponent>();
			audioComponent->setValuesFromJSON(&component);
		}
		else if (componentName == "PhysicsComponent")
		{
			Debug::Log("Adding physics component");
			auto physicsComponent = gameObject->addComponent<PhysicsComponent>();
			state->world;
			physicsComponent->setValuesFromJSON(&component, state->world);

		}
		else if (componentName == "SpriteAnimationComponent")
		{
			auto audioComponent = gameObject->addComponent<SpriteAnimationComponent>();

		}
		//else if (componentName == "SpriteComponent")
		//{
		//	auto audioComponent = gameObject->addComponent<SpriteComponent>();

		//}
		else if (componentName == "TopDownCameraComponent")
		{
			auto audioComponent = gameObject->addComponent<TopDownCameraComponent>();

		}

		Debug::Log("Loading component: " + std::string(componentName));
	}
}
