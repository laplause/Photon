#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Component.h"
#include "PMath.h"
#include <string>

class GameTime;

class GameObject
{
public:
	static const float DefaultVelocity;

	GameObject();
	explicit GameObject(const std::string& objectName);
	virtual ~GameObject();

	virtual void Update(const GameTime&  gameTime);
	virtual void SetPosition(float x, float y, float z);
	virtual void SetPosition(Vec3& position);
	virtual const Vec3& GetPosition() const;
	virtual void MoveForward();
	virtual void MoveBackward();

	bool isEnabled();
	bool isVisible();

	void setEnabled(bool enable);
	void setVisible(bool visible);
	void SetVelocity(const float velocity);
	const float GetVelocity() const;

	const std::string& GetName() const;
	Mat4x4& GetTransform();

protected:
	Mat4x4 mTransform;
	float mVelocity;
	Component* mComponents[Component::COMPONENT_TYPE_MAX];

private:
	bool mEnabled;
	bool mVisible;
	std::string mName;
};
#endif
