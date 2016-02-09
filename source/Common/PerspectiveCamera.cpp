#include "PerspectiveCamera.h"
#include "Input.h"
#include "ServiceLocator.h"
#include "GameObjectCommand.h"

const float PerspectiveCamera::DefaultFieldOfView = PIOVERFOUR;
const float PerspectiveCamera::DefaultNearPlaneDistance = 0.01f;
const float PerspectiveCamera::DefaultFarPlaneDistance = 100.0f;
const float PerspectiveCamera::DefaultMouseSensitivity = 100.0f;

PerspectiveCamera::PerspectiveCamera()
: Camera(), 
mFieldOfView(DefaultFieldOfView), 
mNearPlaneDistance(DefaultNearPlaneDistance), 
mFarPlaneDistance(DefaultFarPlaneDistance),
mMouseSensitivity(DefaultMouseSensitivity)
{

}

PerspectiveCamera::PerspectiveCamera(float fieldOfView, float aspectRatio, float nearPlaneDistance, float farPlaneDistance)
: Camera(), 
mFieldOfView(fieldOfView), 
mAspectRatio(aspectRatio), 
mNearPlaneDistance(nearPlaneDistance), 
mFarPlaneDistance(farPlaneDistance),
mMouseSensitivity(DefaultMouseSensitivity)
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
	Input* inputSystem = ServiceLocator::GetInput();

	GameObjectCommand* command = inputSystem->HandleInput();
	if (command != nullptr)
	{
		command->Execute(*this);
	}

	//RotateLeft();

	//mDirection = mDirection * YRotationMatrix3x3(2.0f * gameTime.DeltaTime());

	UpdateViewMatrix();
}

void PerspectiveCamera::Reset()
{
	Camera::Reset();
	UpdateViewMatrix();
}

void PerspectiveCamera::UpdateViewMatrix()
{
	mViewMatrix = DirectXViewMatrix(mPosition, mDirection, mUp);
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

void PerspectiveCamera::MoveForward()
{
	Vec3 position = GetPosition();
	position += Normalize(mDirection) * (float)(mVelocity * ServiceLocator::GetGameTime()->DeltaTime());

	SetPosition(position);
}

void PerspectiveCamera::MoveBackward()
{
	Vec3 position = GetPosition();
	position -= Normalize(mDirection) * (float)(mVelocity * ServiceLocator::GetGameTime()->DeltaTime());

	SetPosition(position);
}

void PerspectiveCamera::RotateLeft()
{
	float rotationAmount = ServiceLocator::GetInput()->X() /* mMouseSensitivity*/ * mRotationRate * ServiceLocator::GetGameTime()->DeltaTime();

	mDirection = Normalize(mDirection) * YRotationMatrix3x3(rotationAmount);
}

void PerspectiveCamera::RotateRight()
{

}

void PerspectiveCamera::RotateUp()
{

}

void PerspectiveCamera::RotateDown()
{

}