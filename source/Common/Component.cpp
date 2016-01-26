#include "Component.h"

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