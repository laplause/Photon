#include "RotateLeftOrRight.h"
#include "GameObject.h"

RotateLeftOrRight::RotateLeftOrRight() :
GameObjectCommand()
{

}

RotateLeftOrRight::~RotateLeftOrRight()
{

}

void RotateLeftOrRight::Execute(GameObject& go)
{
	go.RotateLeft();
}