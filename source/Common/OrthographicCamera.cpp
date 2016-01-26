#include "OrthographicCamera.h"

const float OrthoGraphicCamera::DefaultNearPlaneDistance = 0;
const float OrthoGraphicCamera::DefaultFarPlaneDistance = 1.0f;

OrthoGraphicCamera::OrthoGraphicCamera(float screenWidth, float screenHeight)
: Camera(), mWidth(screenWidth), mHeight(screenHeight), mNearPlaneDistance(DefaultNearPlaneDistance), mFarPlaneDistance(DefaultFarPlaneDistance)
{

}

OrthoGraphicCamera::OrthoGraphicCamera(float screenWidth, float screenHeight, float near, float far)
: Camera(), mWidth(screenWidth), mHeight(screenHeight), mNearPlaneDistance(near), mFarPlaneDistance(far)
{

}

OrthoGraphicCamera::~OrthoGraphicCamera()
{

}

void OrthoGraphicCamera::Initialize()
{
	UpdateProjectionMatrix();
	Reset();
}

void OrthoGraphicCamera::Update(const GameTime& gameTime)
{
	UpdateViewMatrix();
}

void OrthoGraphicCamera::Reset()
{
	Camera::Reset();
	UpdateViewMatrix();
}

void OrthoGraphicCamera::UpdateViewMatrix()
{
	mViewMatrix = Mat4x4(1, 0, 0, mTransform.row3.x,
								0, 1, 0, mTransform.row3.y,
								0, 0, 1, 0,
								0, 0, 0, 1);
}

void OrthoGraphicCamera::UpdateProjectionMatrix()
{
	mProjectionMatrix = DirectXOrthoMatrix(mWidth, mHeight, mNearPlaneDistance, mFarPlaneDistance);
}

void OrthoGraphicCamera::SetPosition(float x, float y, float z)
{
	Camera::SetPosition(x, y, z);
}

void OrthoGraphicCamera::SetPosition(Vec3& position)
{
	Camera::SetPosition(position);
}