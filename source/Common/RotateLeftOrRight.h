#ifndef ROTATELEFTORRIGHT_H
#define ROTATELEFTORRIGHT_H

#include "GameObjectCommand.h"

class RotateLeftOrRight : public GameObjectCommand
{
public:
	RotateLeftOrRight();
	virtual ~RotateLeftOrRight();
	virtual void Execute(GameObject& go);

private:
	RotateLeftOrRight(const RotateLeftOrRight& rhs);
	const RotateLeftOrRight& operator=(const RotateLeftOrRight& rhs);
};
#endif