#ifndef PERSPECTIVECAMERA_H
#define PERSPECTIVECAMERA_H

#include "Camera.h"

class PerspectiveCamera : public Camera
{
public:
	PerspectiveCamera();
	PerspectiveCamera(float fieldOfView, float aspectRatio, float nearPlaneDistance, float farPlaneDistance);
	virtual ~PerspectiveCamera();

	virtual void Initialize();
	virtual void Update(const GameTime& gameTime);
	virtual void Reset();

	virtual void UpdateViewMatrix();
	virtual void UpdateProjectionMatrix();

	virtual void SetPosition(float x, float y, float z);
	virtual void SetPosition(Vec3& position);

	virtual void MoveForward();
	virtual void MoveBackward();
	virtual void MoveLeft();
	virtual void MoveRight();

	void SetAspectRatio(float aspectRatio);

	static const float DefaultFieldOfView;
	static const float DefaultAspectRatio;
	static const float DefaultNearPlaneDistance;
	static const float DefaultFarPlaneDistance;

protected:
	virtual void CalculateRotation();

	static const float DefaultMouseSensitivity;

	float mMouseSensitivity;
	float mFieldOfView;
	float mAspectRatio;
	float mNearPlaneDistance;
	float mFarPlaneDistance;
};
#endif