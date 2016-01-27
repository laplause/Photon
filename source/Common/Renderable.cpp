#include "Renderable.h"
#include "GameObject.h"

Renderable::Renderable(const std::string& modelName) :
Component(Component::RENDERABLE), 
mModel(nullptr),
mParent(nullptr)
{
}

Renderable::Renderable(Model* model, GameObject* go) :
Component(Component::RENDERABLE),
mModel(model),
mParent(go)
{
}

Renderable::~Renderable()
{

}

const Model* Renderable::GetModel() const
{
	return mModel;
}

Mat4x4& Renderable::GetTransform()
{
	return mParent->GetTransform();
}