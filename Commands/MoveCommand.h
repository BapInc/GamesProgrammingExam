#ifndef MOVECOMMAND_H
#define MOVECOMMAND_H

class MoveCommand
{
public:
	MoveCommand(int& xposition, int& yposition);
	MoveCommand(int& xposition, int& yposition);
	~MoveCommand();

	virtual void Execute();

private:
	int x;
	int y;
	bool isEnemy;
};

#endif // !MOVECOMMAND_H