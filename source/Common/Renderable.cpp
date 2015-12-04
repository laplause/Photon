#include "Renderable.h"
using namespace RenderCore;

Renderable::Renderable(const std::string& modelName) :
Component(Core::Component::RENDERABLE), 
mModel(nullptr),
mTransform()
{
	mTransform = CreateIdentity4x4();
}

Renderable::Renderable(Model* model) :
Component(Core::Component::RENDERABLE),
mModel(model),
mTransform()
{
	mTransform = CreateIdentity4x4();
}

Renderable::~Renderable()
{

}

const Model* Renderable::GetModel() const
{
	return mModel;
}

const Mat4x4& Renderable::GetTransform() const
{
	return mTransform;
}

void Renderable::SetPosition(float x, float y, float z)
{
	mTransform.row0.w = x;
	mTransform.row1.w = y;
	mTransform.row2.w = z;
}

void Renderable::SetPosition(Vec3& position)
{
	Renderable::SetPosition(position.x, position.y, position.z);
}