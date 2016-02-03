#ifndef GAMEOBJECTCOMMAND_H
#define GAMEOBJECTCOMMAND_H

class GameObject;

class GameObjectCommand
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