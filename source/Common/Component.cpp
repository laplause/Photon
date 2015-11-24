#include "Component.h"
using namespace Core;

Component::Component(ComponentType type) :
mType(type)
{

}

Component::~Component()
{

}

const Component::ComponentType Component::GetType() const
{
	return mType;
}