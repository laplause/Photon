#ifndef GAMEOBJECTCOMMAND_H
#define GAMEOBJECTCOMMAND_H

#include "Command.h"

class GameObject;

class GameObjectCommand : public Command
{
public:
	GameObjectCommand();
	virtual ~GameObjectCommand();
	virtual void Execute(GameObject& go) = 0;

private:
	GameObjectCommand(const GameObjectCommand& rhs);
	const GameObjectCommand& operator=(const GameObjectCommand& rhs);
};
#endif