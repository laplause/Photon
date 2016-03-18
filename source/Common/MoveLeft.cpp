#include "MoveLeft.h"
#include "GameObject.h"

MoveLeft::MoveLeft() :
GameObjectCommand()
{

}

MoveLeft::~MoveLeft()
{

}

void MoveLeft::Execute(GameObject& go)
{
	go.MoveLeft();
}