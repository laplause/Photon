#ifndef MOVEFORWARD_H
#define MOVEFORWARD_H

#include "GameObjectCommand.h"

class MoveForward : public GameObjectCommand
{
public:
	MoveForward();
	MoveForward(const MoveForward& rhs) = delete;
	const MoveForward& operator=(const MoveForward& rhs) = delete;

	virtual ~MoveForward();
	virtual void Execute(GameObject& go);
};
#endif