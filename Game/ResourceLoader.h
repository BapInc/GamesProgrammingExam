#ifndef RESOURCELOADER_H
#define RESOURCELOADER_H
#include <string>
#include "../GameStates/LevelState.h"

class ResourceLoader {
public:
	static void loadGameObjectsFromFile(std::string path, LevelState* state);
	static void addComponents(rapidjson::Value& go, std::shared_ptr<GameObject>& gameObject, LevelState* state);
};

#endif