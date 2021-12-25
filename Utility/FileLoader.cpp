#include "FileLoader.h"
#include "../rapidjson/istreamwrapper.h"
#include <fstream>
#include <iostream>

std::shared_ptr<rapidjson::Document> FileLoader::loadJSONDocument(std::string path)
{
	std::ifstream fis(path);
	rapidjson::IStreamWrapper isw(fis);
	auto d = std::make_shared<rapidjson::Document>();
	d->ParseStream(isw);
	return d;
}

