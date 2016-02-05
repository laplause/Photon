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
	mTransform.row0.w = position.x;
	mTransform.row1.w = position.y;
	mTransform.row2.w = position.z;
}

const Vec3 Camera::GetPosition() const
{
	return Vec3(mTransform.row0.w, mTransform.row1.w, mTransform.row2.w);
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