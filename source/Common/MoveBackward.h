#ifndef MOVEBACKWARD_H
#define MOVEBACKWARD_H

#include "GameObjectCommand.h"

class MoveBackward : public GameObjectCommand
{
public:
	MoveBackward();
	virtual ~MoveBackward();
	virtual void Execute(GameObject& go);

private:
	MoveBackward(const MoveBackward& rhs);
	const MoveBackward& operator=(const MoveBackward& rhs);
};
#endif