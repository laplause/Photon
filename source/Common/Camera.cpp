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
	mTransform.row3.x = x;
	mTransform.row3.y = y;
	mTransform.row3.z = z;
}

void Camera::SetPosition(Vec3& position)
{
	mTransform.row3 = Vec4(position, 1.0f);
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