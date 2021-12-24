#ifndef MOVECOMMAND_H
#define MOVECOMMAND_H

class MoveCommand
{
public:
	//MoveCommand(float& xposition, float& yposition);
	MoveCommand(float& xposition, float& yposition);
	~MoveCommand();

	virtual void Execute();

private:
	float x;
	float y;
	bool isEnemy;
};

#endif // !MOVECOMMAND_H