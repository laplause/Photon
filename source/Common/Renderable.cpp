#include "Renderable.h"
using namespace RenderCore;

Renderable::Renderable(const std::string& modelName) :
Component(Core::Component::RENDERABLE), mModel(nullptr)
{

}

Renderable::Renderable(Model* model) :
Component(Core::Component::RENDERABLE),
mModel(model)
{

}

Renderable::~Renderable()
{

}

const Model* Renderable::GetModel() const
{
	return mModel;
}