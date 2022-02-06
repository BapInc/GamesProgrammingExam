#ifndef MOVECOMMAND_H
#define MOVECOMMAND_H

#include <stack>
#include <iostream>
#include "glm/glm.hpp"

class MoveCommand
{
public:
	//MoveCommand(float& xposition, float& yposition);
	MoveCommand(glm::vec2& position);
	~MoveCommand();

	virtual void Execute();

private:
	glm::vec2 pos;
};

#endif // !MOVECOMMAND_H