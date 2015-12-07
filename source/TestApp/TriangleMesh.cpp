#include "TriangleMesh.h"
#include "DirectXRenderer.h"

TriangleMesh::TriangleMesh(const std::string& meshName) :
Mesh(meshName)
{

}

TriangleMesh::~TriangleMesh()
{

}

void TriangleMesh::Initialize(DirectXRenderer* renderer)
{
	Vertex* vertices;
	unsigned long* indices;
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;

	mVertexCount = 3;
	mIndexCount = 3;

	vertices = new Vertex[mVertexCount];
	indices = new unsigned long[mIndexCount];

	vertices[0].position = Vec4(-1.0f, -1.0f, 0, 1.0f);
	vertices[0].color = Vec4(1.0f, 0, 0, 1.0f);

	vertices[1].position = Vec4(0, 1.0f, 0, 1.0f);
	vertices[1].color = Vec4(1.0f, 0, 0, 1.0f);

	vertices[2].position = Vec4(1.0f, -1.0f, 0, 1.0f);
	vertices[2].color = Vec4(1.0f, 0, 0, 1.0f);

	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 2;

	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(Vertex)* mVertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	vertexData.pSysMem = vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	renderer->Direct3DDevice()->CreateBuffer(&vertexBufferDesc, &vertexData, &mVertexBuffer);

	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(unsigned long)* mIndexCount;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	indexData.pSysMem = indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	renderer->Direct3DDevice()->CreateBuffer(&indexBufferDesc, &indexData, &mIndexBuffer);

	delete [] vertices;
	vertices = nullptr;

	delete [] indices;
	indices = nullptr;
}

const unsigned int TriangleMesh::VertexSize() const
{
	return sizeof(Vertex);
}