#include "MoveBackward.h"
#include "GameObject.h"

MoveBackward::MoveBackward() :
GameObjectCommand()
{
	
}

MoveBackward::~MoveBackward()
{

}

void MoveBackward::Execute(GameObject& go)
{
	go.MoveBackward();
}