#ifndef RENDERABLE_H
#define RENDERABLE_H

#include "Component.h"
#include "PMath.h"
#include <string>

class Model;
class GameObject;

class Renderable : public Component
{
public:
	Renderable(const std::string& modelName);
	Renderable(Model* model, GameObject* go);
	virtual ~Renderable();

	const Model* GetModel() const;
	Mat4x4& GetTransform();

private:
	Model* mModel;
	GameObject* mParent;
};
#endif