#include "MoveCommand.h"
#include <iostream>
#include <string>


MoveCommand::MoveCommand(glm::vec2& position)
{
	pos = position;
}


MoveCommand::~MoveCommand()
{
}

void MoveCommand::Execute()
{

}
