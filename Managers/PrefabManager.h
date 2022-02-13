#ifndef RESOURCELOADER_H
#define RESOURCELOADER_H
#include <string>
#include "../GameStates/LevelState.h"
#include <map>

class PrefabManager {
public:
	void loadGameObjectsFromFile(std::string path, LevelState* state);
	void addComponents(rapidjson::Value& go, std::shared_ptr<GameObject>& gameObject, LevelState* state);
	std::shared_ptr<GameObject> getPrefab(std::string name, LevelState* state);

private:
	std::map<std::string, std::shared_ptr<GameObject>> prefabs;
};

#endif