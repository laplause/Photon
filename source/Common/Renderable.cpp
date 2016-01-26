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

void Renderable::SetPosition(float x, float y, float z)
{
	GetTransform().row0.w = x;
	GetTransform().row1.w = y;
	GetTransform().row2.w = z;
}

void Renderable::SetPosition(Vec3& position)
{
	Renderable::SetPosition(position.x, position.y, position.z);
}