#ifndef CAMERA_H
#define CAMERA_H

#include "GameObject.h"
#include "PMath.h"
#include "GameTime.h"

namespace RenderCore
{
	class Camera : public Core::GameObject
	{
	public:
		Camera();
		virtual ~Camera();

		virtual void Initialize() = 0;
		virtual void Update(const Core::GameTime& gameTime) = 0;

		virtual void Reset() = 0;

		virtual void SetPosition(float x, float y, float z);
		virtual void SetPosition(PMath::Vec3& position);

		const PMath::Vec4& GetPosition() const;
		const PMath::Vec4& GetForward() const;
		const PMath::Vec4& GetUp() const;
		const PMath::Vec4& GetRight() const;

		const PMath::Mat4x4& ViewMatrix() const;
		const PMath::Mat4x4& ProjectionMatrix() const;
		const PMath::Mat4x4& ViewProjectionMatrix() const;

	protected:
		PMath::Mat4x4 mViewMatrix;
		PMath::Mat4x4 mProjectionMatrix;

	private:
		Camera(const Camera& rhs);
		Camera& operator=(const Camera& rhs);
	};
}
#endif