#include "GameObject.h"
using namespace Core;

GameObject::GameObject()
:mEnabled(true), mVisible(true), mTransform(PMath::CreateIdentity4x4())
{
	for (int i = 0; i < Component::COMPONENT_TYPE_MAX; i++)
	{
		mComponents[i] = nullptr;
	}
}

GameObject::GameObject(const std::string& objectName)
: mEnabled(true), mVisible(true), mName(objectName), mTransform(PMath::CreateIdentity4x4())
{
	for (int i = 0; i < Component::COMPONENT_TYPE_MAX; i++)
	{
		mComponents[i] = nullptr;
	}
}

GameObject::~GameObject()
{

}

bool GameObject::isEnabled()
{
	return mEnabled;
}

bool GameObject::isVisible()
{
	return mVisible;
}

void GameObject::setEnabled(bool enable)
{
	mEnabled = enable;
}

void GameObject::setVisible(bool visible)
{
	mVisible = visible;
}

const std::string& GameObject::GetName() const
{
	return mName;
}

const PMath::Mat4x4& GameObject::GetTransform() const
{
	return mTransform;
}