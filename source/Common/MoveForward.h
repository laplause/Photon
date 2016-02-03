#ifndef MOVEFORWARD_H
#define MOVEFORWARD_H

#include "GameObjectCommand.h"

class MoveForward : public GameObjectCommand
{
public:
	MoveForward();
	virtual ~MoveForward();
	virtual void Execute(GameObject& go);

private:
	MoveForward(const MoveForward& rhs);
	const MoveForward& operator=(const MoveForward& rhs);
};
#endif