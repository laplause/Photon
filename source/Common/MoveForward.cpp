#include "MoveForward.h"
#include "GameObject.h"

MoveForward::MoveForward() :
GameObjectCommand()
{

}

MoveForward::~MoveForward()
{

}

void MoveForward::Execute(GameObject& go)
{
	go.MoveForward();
}