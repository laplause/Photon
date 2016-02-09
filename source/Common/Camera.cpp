#include "Camera.h"

Camera::Camera() : 
GameObject(), 
mViewMatrix(), 
mProjectionMatrix(),
mPosition(),
mDirection(),
mUp()
{

}

Camera::~Camera()
{

}

void Camera::Reset()
{
	mTransform = CreateIdentity4x4();
	mPosition = Vec3(0, 0, 0);
	mDirection = Vec3(0, 0, 1.0f);
	mUp = Vec3(0, 1.0f, 0);
}

void Camera::Initialize()
{
	Reset();
}

void Camera::Update(const GameTime& gameTime)
{
	
}

void Camera::SetPosition(float x, float y, float z)
{
	SetPosition(Vec3(x, y, z));
}

void Camera::SetPosition(Vec3& position)
{
	mPosition = position;
}

const Vec3 Camera::GetPosition() const
{
	return mPosition;
}

const Mat4x4& Camera::ViewMatrix() const
{
	return mViewMatrix;
}

const Mat4x4& Camera::ProjectionMatrix() const
{
	return mProjectionMatrix;
}

const Mat4x4& Camera::ViewProjectionMatrix() const
{
	return mViewMatrix * mProjectionMatrix;
}

const Vec4& Camera::GetVec4Position() const
{
	return mTransform.row3;
}