#include "PerspectiveCamera.h"
using namespace RenderCore;

const float PerspectiveCamera::DefaultFieldOfView = PMath::PIOVERFOUR;
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

void PerspectiveCamera::Update(const Core::GameTime& gameTime)
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
	PMath::Vec3 position = PMath::Vec3(mTransform.row3.x, mTransform.row3.y, mTransform.row3.z);
	PMath::Vec3 direction = PMath::Vec3(mTransform.row2.x, mTransform.row2.y, mTransform.row2.z);
	PMath::Vec3 up = PMath::Vec3(mTransform.row1.x, mTransform.row1.y, mTransform.row1.z);

	mViewMatrix = PMath::DirectXViewMatrix(position, direction, up);
}

void PerspectiveCamera::UpdateProjectionMatrix()
{
	mProjectionMatrix = PMath::DirectXPerspectiveMatrix(mFieldOfView, mAspectRatio, mNearPlaneDistance, mFarPlaneDistance);
}

void PerspectiveCamera::SetAspectRatio(float aspectRatio)
{
	mAspectRatio = aspectRatio;
}

void PerspectiveCamera::SetPosition(float x, float y, float z)
{
	Camera::SetPosition(x, y, z);
	UpdateViewMatrix();
}

void PerspectiveCamera::SetPosition(PMath::Vec3& position)
{
	mTransform.row3 = PMath::Vec4(position, 1.0f);
}