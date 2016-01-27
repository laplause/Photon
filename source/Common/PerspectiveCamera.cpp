#include "PerspectiveCamera.h"

const float PerspectiveCamera::DefaultFieldOfView = PIOVERFOUR;
const float PerspectiveCamera::DefaultNearPlaneDistance = 0.01f;
const float PerspectiveCamera::DefaultFarPlaneDistance = 100.0f;

PerspectiveCamera::PerspectiveCamera()
: Camera(), mFieldOfView(DefaultFieldOfView), mNearPlaneDistance(DefaultNearPlaneDistance), mFarPlaneDistance(DefaultFarPlaneDistance)
{

}

PerspectiveCamera::PerspectiveCamera(float fieldOfView, float aspectRatio, float nearPlaneDistance, float farPlaneDistance)
: Camera(), mFieldOfView(fieldOfView), mAspectRatio(aspectRatio), mNearPlaneDistance(nearPlaneDistance), mFarPlaneDistance(farPlaneDistance)
{

}

PerspectiveCamera::~PerspectiveCamera()
{

}

void PerspectiveCamera::Initialize()
{
	UpdateProjectionMatrix();
	Reset();
}

void PerspectiveCamera::Update(const GameTime& gameTime)
{
	UpdateViewMatrix();
}

void PerspectiveCamera::Reset()
{
	Camera::Reset();
	UpdateViewMatrix();
}

void PerspectiveCamera::UpdateViewMatrix()
{
	Vec3 position = Vec3(mTransform.row3.x, mTransform.row3.y, mTransform.row3.z);
	Vec3 direction = Vec3(mTransform.row2.x, mTransform.row2.y, mTransform.row2.z);
	Vec3 up = Vec3(mTransform.row1.x, mTransform.row1.y, mTransform.row1.z);

	mViewMatrix = DirectXViewMatrix(position, direction, up);
}

void PerspectiveCamera::UpdateProjectionMatrix()
{
	mProjectionMatrix = DirectXPerspectiveMatrix(mFieldOfView, mAspectRatio, mNearPlaneDistance, mFarPlaneDistance);
}

void PerspectiveCamera::SetAspectRatio(float aspectRatio)
{
	mAspectRatio = aspectRatio;
}

void PerspectiveCamera::SetPosition(float x, float y, float z)
{
	SetPosition(Vec3(x, y, z));
}

void PerspectiveCamera::SetPosition(Vec3& position)
{
	Camera::SetPosition(position);
	UpdateViewMatrix();
}