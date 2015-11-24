#ifndef RENDERABLE_H
#define RENDERABLE_H

#include "Component.h"
#include <string>

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

	private:
		Model* mModel;
	};
}
#endif