#ifndef MOVERIGHT_H
#define MOVERIGHT_H

#include "GameObjectCommand.h"

class MoveRight : public GameObjectCommand
{
public:
	MoveRight();
	MoveRight(const MoveRight& rhs) = delete;
	const MoveRight& operator=(const MoveRight& rhs) = delete;

	virtual ~MoveRight();
	virtual void Execute(GameObject& go);
};
#endif