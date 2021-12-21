#include "Debug.h"
#include <Windows.h>
#include <iostream>


Debug* Debug::getInstance()
{
	static Debug* instance = new Debug;
	return instance;
}

Debug* Debug::Log(const std::string& log, Logs type)
{

	static Debug* instance = new Debug;

	int outPutHandle = 15; //Text set to white
	std::string initialText = "[LOG]";
	std::string temp = "";
	switch (type)
	{
	case ALERT:
		outPutHandle = 4;
		initialText = "[ERROR]";
		break;
	case WARNING:

		outPutHandle = 14;
		initialText = "[WARNING]";
		break;
	case SUCCESS:

		outPutHandle = 10;
		initialText = "[SUCCESS]";
		break;
	default:
		break;
	}

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), outPutHandle);
	std::cout << "=======================================" << std::endl;
	temp = initialText + log;
	std::cout << temp << std::endl;
	std::cout << "=======================================" << std::endl;
	std::cout << "" << std::endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

	return instance;
}
