#include "Model.h"
#include "Common.h"
using namespace RenderCore;

Model::Model(const std::string& modelName) :
mName(modelName), mMeshList()
{

}

Model::~Model()
{
	// Delete Meshes
	for (std::vector<Mesh*>::iterator it = mMeshList.begin(); it != mMeshList.end(); ++it)
	{
		DELETEOBJECT(*it);
	}
}

const std::string& Model::ModelName() const
{
	return mName;
}

const std::vector<Mesh*>& Model::GetMeshes() const
{
	return mMeshList;
}

void Model::AddMesh(Mesh* mesh)
{
	mMeshList.push_back(mesh);
}