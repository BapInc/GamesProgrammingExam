#include "MoveCommand.h"
#include <iostream>
#include <string>


/*MoveCommand::MoveCommand(float& xposition, float& yposition)
{
	isEnemy = true;
	x = xposition;
	y = yposition;
}*/

MoveCommand::MoveCommand(float& xposition, float& yposition)
{
	//isEnemy = false;
	x = xposition;
	y = yposition;
}


MoveCommand::~MoveCommand()
{
}

void MoveCommand::Execute()
{

	std::string m_tempString = "MOVE_" + std::to_string(x) + '_' + std::to_string(y) + '_';
	std::cout << m_tempString;

	//send message with x and y values;
	/*if (isEnemy == false)
	{
		std::string m_tempString = "MOVE_" + std::to_string(x) + '_' + std::to_string(y) + '_';
		std::cout << m_tempString;
	}
	else
	{
		std::string m_tempString = "ENEMY_MOVE_" + std::to_string(x) + '_' + std::to_string(y) + '_';
	}*/
}