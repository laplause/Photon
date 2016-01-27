#ifndef MESH_H
#define MESH_H

#include <string>
#include <d3d11_1.h>

class DirectXRenderer;
class Model;

class Mesh
{
public:
	Mesh(const std::string& meshName, Model* model);
	virtual ~Mesh();

	virtual void Initialize(DirectXRenderer* renderer) = 0;
	virtual const unsigned int VertexSize() const = 0;

	const std::string& MeshName() const;
	Model* ParentModel() const;

	ID3D11Buffer* GetVertexBuffer() const;
	ID3D11Buffer* GetIndexBuffer() const;
	const int NumIndices() const;

protected:
	std::string mName;
	Model* mParentModel;

	ID3D11Buffer* mVertexBuffer;
	ID3D11Buffer* mIndexBuffer;
	int mVertexCount;
	int mIndexCount;
};
#endif