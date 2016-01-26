#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Component.h"
#include "PMath.h"
#include <string>

class GameObject
{
public:
	GameObject();
	explicit GameObject(const std::string& objectName);
	virtual ~GameObject();

	bool isEnabled();
	bool isVisible();

	void setEnabled(bool enable);
	void setVisible(bool visible);

	const std::string& GetName() const;
	Mat4x4& GetTransform();

protected:
	Mat4x4 mTransform;
	Component* mComponents[Component::COMPONENT_TYPE_MAX];

private:
	bool mEnabled;
	bool mVisible;
	std::string mName;
};
#endif
