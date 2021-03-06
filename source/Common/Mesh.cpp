#include "Mesh.h"
#include "Common.h"

Mesh::Mesh(const std::string& meshName, Model* model) :
mName(meshName),
mParentModel(model),
mIndexBuffer(nullptr),
mVertexBuffer(nullptr),
mIndexCount(0),
mVertexCount(0)
{

}

Mesh::~Mesh()
{
	RELEASEOBJECT(mVertexBuffer);
	RELEASEOBJECT(mIndexBuffer);
}

const std::string& Mesh::MeshName() const
{
	return mName;
}

Model* Mesh::ParentModel() const
{
	return mParentModel;
}

void Mesh::Initialize(DirectXRenderer* renderer)
{

}

ID3D11Buffer* Mesh::GetVertexBuffer() const
{
	return mVertexBuffer;
}

ID3D11Buffer* Mesh::GetIndexBuffer() const
{
	return mIndexBuffer;
}

const int Mesh::NumIndices() const
{
	return mIndexCount;
}