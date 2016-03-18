#include "PerspectiveCamera.h"
#include "Input.h"
#include "ServiceLocator.h"
#include "GameObjectCommand.h"

const float PerspectiveCamera::DefaultFieldOfView = PIOVERFOUR;
const float PerspectiveCamera::DefaultNearPlaneDistance = 0.01f;
const float PerspectiveCamera::DefaultFarPlaneDistance = 100.0f;
const float PerspectiveCamera::DefaultMouseSensitivity = 25.0f;

PerspectiveCamera::PerspectiveCamera()
: Camera(), 
mFieldOfView(DefaultFieldOfView), 
mNearPlaneDistance(DefaultNearPlaneDistance), 
mFarPlaneDistance(DefaultFarPlaneDistance),
mMouseSensitivity(DefaultMouseSensitivity)
{
	SetVelocity(20.0f);
}

PerspectiveCamera::PerspectiveCamera(float fieldOfView, float aspectRatio, float nearPlaneDistance, float farPlaneDistance)
: Camera(), 
mFieldOfView(fieldOfView), 
mAspectRatio(aspectRatio), 
mNearPlaneDistance(nearPlaneDistance), 
mFarPlaneDistance(farPlaneDistance),
mMouseSensitivity(DefaultMouseSensitivity)
{
	SetVelocity(20.0f);
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

	std::vector<GameObjectCommand*> commands = inputSystem->HandleInput();

	for (auto& it = commands.begin(); it != commands.end(); ++it)
	{
		GameObjectCommand* command = *it;
		if (command != nullptr)
		{
			command->Execute(*this);
		}
	}

	CalculateRotation();

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
	mRight = mViewMatrix.row0;
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

void PerspectiveCamera::MoveLeft()
{
	Vec3 position = GetPosition();
	position -= Normalize(mRight) * (float)(mVelocity * ServiceLocator::GetGameTime()->DeltaTime());

	SetPosition(position);
}

void PerspectiveCamera::MoveRight()
{
	Vec3 position = GetPosition();
	position += Normalize(mRight) * (float)(mVelocity * ServiceLocator::GetGameTime()->DeltaTime());

	SetPosition(position);
}

void PerspectiveCamera::CalculateRotation()
{
	float rotationAmount = mMouseSensitivity * mRotationRate * ServiceLocator::GetGameTime()->DeltaTime();
	Vec2 rotations(rotationAmount * ServiceLocator::GetInput()->X(), rotationAmount * ServiceLocator::GetInput()->Y());

	Mat3x3 transform = YRotationMatrix3x3(rotations.x) * VectorRotationMatrix(rotations.y, mRight);
	mUp = mUp * transform;
	mDirection = mDirection * transform;
}