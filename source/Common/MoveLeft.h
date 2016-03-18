#ifndef MOVELEFT_H
#define MOVELEFT_H

#include "GameObjectCommand.h"

class MoveLeft : public GameObjectCommand
{
public:
	MoveLeft();
	virtual ~MoveLeft();
	virtual void Execute(GameObject& go);

private:
	MoveLeft(const MoveLeft& rhs);
	const MoveLeft& operator=(const MoveLeft& rhs);
};
#endif