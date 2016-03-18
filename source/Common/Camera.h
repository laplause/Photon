#ifndef CAMERA_H
#define CAMERA_H

#include "GameObject.h"
#include "PMath.h"
#include "GameTime.h"

class Camera : public GameObject
{
public:
	Camera();
	virtual ~Camera();

	virtual void Initialize() = 0;
	virtual void Update(const GameTime& gameTime) = 0;

	virtual void Reset() = 0;

	virtual void SetPosition(float x, float y, float z);
	virtual void SetPosition(Vec3& position);

	virtual const Vec3 GetPosition() const;
	const Vec4& GetVec4Position() const;
	const Vec3& GetForward() const;
	const Vec3& GetUp() const;
	const Vec3& GetRight() const;

	const Mat4x4& ViewMatrix() const;
	const Mat4x4& ProjectionMatrix() const;
	const Mat4x4& ViewProjectionMatrix() const;

protected:
	Mat4x4 mViewMatrix;
	Mat4x4 mProjectionMatrix;

	Vec3 mPosition;
	Vec3 mDirection;
	Vec3 mRight;
	Vec3 mUp;

private:
	Camera(const Camera& rhs);
	Camera& operator=(const Camera& rhs);
};
#endif