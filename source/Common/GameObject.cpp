#include "GameObject.h"
#include "ServiceLocator.h"
#include "GameTime.h"

const float GameObject::DefaultVelocity = 5.0f;

GameObject::GameObject()
:mEnabled(true), 
mVisible(true), 
mTransform(CreateIdentity4x4()),
mVelocity(DefaultVelocity)
{
	for (int i = 0; i < Component::COMPONENT_TYPE_MAX; i++)
	{
		mComponents[i] = nullptr;
	}
}

GameObject::GameObject(const std::string& objectName)
: mEnabled(true), 
mVisible(true), 
mName(objectName), 
mTransform(CreateIdentity4x4()),
mVelocity(DefaultVelocity)
{
	for (int i = 0; i < Component::COMPONENT_TYPE_MAX; i++)
	{
		mComponents[i] = nullptr;
	}
}

GameObject::~GameObject()
{

}

void GameObject::Update(const GameTime& gameTime)
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

void GameObject::SetVelocity(const float velocity)
{
	mVelocity = velocity;
}

const float GameObject::GetVelocity() const
{
	return mVelocity;
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

const Vec3 GameObject::GetPosition() const
{
	return Vec3(mTransform.row0.w, mTransform.row1.w, mTransform.row2.w);
}

void GameObject::MoveForward()
{
	Vec3 position = GetPosition();
	position.z += (float)(mVelocity*ServiceLocator::GetGameTime()->DeltaTime());

	SetPosition(position);
}

void GameObject::MoveBackward()
{
	Vec3 position = GetPosition();
	position.z -= (float)(mVelocity*ServiceLocator::GetGameTime()->DeltaTime());

	SetPosition(position);
}