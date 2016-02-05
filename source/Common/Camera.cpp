#include "Camera.h"

Camera::Camera() : GameObject(), mViewMatrix(), mProjectionMatrix()
{

}

Camera::~Camera()
{

}

void Camera::Reset()
{
	mTransform = CreateIdentity4x4();
}

void Camera::Initialize()
{
	
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
	mTransform.row3 = Vec4(position, 1.0f);
}

const Vec3 Camera::GetPosition() const
{
	Vec4 position = mTransform.row3;
	return Vec3(position.x, position.y, position.z);
}

const Vec4& Camera::GetVec4Position() const
{
	return mTransform.row3;
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