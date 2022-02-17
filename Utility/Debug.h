#ifndef DEBUG
#define DEBUG

#include <string>
#include "glm/glm.hpp"


enum Logs
{
	LOG = 1, ALERT, WARNING, SUCCESS
};

class Debug
{
public:

	static Debug* getInstance();

	static Debug* Log(const std::string& log, Logs type = LOG);
	static Debug* Log(const glm::vec2& log, Logs type = LOG);
private:

	void setupLogFile();


};

#endif