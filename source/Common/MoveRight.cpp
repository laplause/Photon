#include "MoveRight.h"
#include "GameObject.h"

MoveRight::MoveRight() :
GameObjectCommand()
{

}

MoveRight::~MoveRight()
{

}

void MoveRight::Execute(GameObject& go)
{
	go.MoveRight();
}