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