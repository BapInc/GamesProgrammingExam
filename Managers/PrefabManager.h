#ifndef PREFABMANAGER_H
#define PREFABMANAGER_H
#include <string>
#include "../GameStates/LevelState.h"
#include <map>

class PrefabManager{
public:
	void loadGameObjectsFromFile(std::string path, LevelState* state);
	void addComponents(rapidjson::Value& go, std::shared_ptr<GameObject>& gameObject, LevelState* state);
	std::shared_ptr<GameObject> getPrefab(std::string name, LevelState* state, glm::vec2 pos, b2World* world);
	void clearPrefabs();

private:
	std::map<std::string, std::shared_ptr<GameObject>> prefabs;
};

#endif