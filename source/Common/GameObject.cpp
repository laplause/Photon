#include "GameObject.h"

GameObject::GameObject()
:mEnabled(true), mVisible(true), mTransform(CreateIdentity4x4())
{
	for (int i = 0; i < Component::COMPONENT_TYPE_MAX; i++)
	{
		mComponents[i] = nullptr;
	}
}

GameObject::GameObject(const std::string& objectName)
: mEnabled(true), mVisible(true), mName(objectName), mTransform(CreateIdentity4x4())
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

Mat4x4& GameObject::GetTransform()
{
	return mTransform;
}

void GameObject::SetPosition(float x, float y, float z)
{
	mTransform.row0.w = x;
	mTransform.row1.w = y;
	mTransform.row2.w = z;
}

void GameObject::SetPosition(Vec3& position)
{
	SetPosition(position.x, position.y, position.z);
}