#ifndef RENDERABLE_H
#define RENDERABLE_H

#include "Component.h"
#include "PMath.h"
#include <string>
using namespace PMath;

namespace RenderCore
{
	class Model;

	class Renderable : public Core::Component
	{
	public:
		Renderable(const std::string& modelName);
		Renderable(Model* model);
		virtual ~Renderable();

		const Model* GetModel() const;
		const Mat4x4& GetTransform() const;

	protected:
		Mat4x4 mTransform;

	private:
		Model* mModel;
	};
}
#endif