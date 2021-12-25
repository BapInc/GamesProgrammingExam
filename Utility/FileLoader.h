#ifndef FILELOADER_H
#define FILELOADER_H

#include "../rapidjson/document.h"
#include <string>
#include <memory> 

class FileLoader {
public:
	static std::shared_ptr<rapidjson::Document> loadJSONDocument(std::string path);
};

#endif