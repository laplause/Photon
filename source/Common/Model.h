#ifndef MODEL_H
#define MODEL_H

#include <string>
#include <vector>
#include "Mesh.h"

namespace RenderCore
{
	class Model
	{
	public:
		Model(const std::string& modelName);
		virtual ~Model();

		const std::string& ModelName() const;
		const std::vector<Mesh*>& GetMeshes() const;

		void AddMesh(Mesh* mesh);

	private:
		std::string mName;
		std::vector<Mesh*> mMeshList;
	};
}
#endif