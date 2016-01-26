#ifndef ORTHOGRAPHICCAMERA_H
#define ORTHOGRAPHICCAMERA_H

#include "Camera.h"

class OrthoGraphicCamera : public Camera
{
public:
	OrthoGraphicCamera(float screenWidth, float screenHeight);
	OrthoGraphicCamera(float screenWidth, float screenHeight, float near, float far);
	virtual ~OrthoGraphicCamera();

	virtual void Initialize();
	virtual void Update(const GameTime& gameTime);
	virtual void Reset();

	virtual void UpdateViewMatrix();
	virtual void UpdateProjectionMatrix();

	virtual void SetPosition(float x, float y, float z);
	virtual void SetPosition(Vec3& position);

	static const float DefaultNearPlaneDistance;
	static const float DefaultFarPlaneDistance;

protected:
	float mWidth;
	float mHeight;
	float mNearPlaneDistance;
	float mFarPlaneDistance;
};
#endif