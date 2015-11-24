#include "Camera.h"
using namespace RenderCore;

Camera::Camera() : GameObject(), mViewMatrix(), mProjectionMatrix()
{

}

Camera::~Camera()
{

}

void Camera::Reset()
{
	mTransform = PMath::CreateIdentity4x4();
}

void Camera::Initialize()
{
	
}

void Camera::Update(const Core::GameTime& gameTime)
{
	
}

void Camera::SetPosition(float x, float y, float z)
{
	mTransform.row3.x = x;
	mTransform.row3.z = y;
	mTransform.row3.z = z;
}

void Camera::SetPosition(PMath::Vec3& position)
{
	mTransform.row3 = PMath::Vec4(position, 1.0f);
}

const PMath::Mat4x4& Camera::ViewMatrix() const
{
	return mViewMatrix;
}

const PMath::Mat4x4& Camera::ProjectionMatrix() const
{
	return mProjectionMatrix;
}

const PMath::Mat4x4& Camera::ViewProjectionMatrix() const
{
	return mViewMatrix * mProjectionMatrix;
}