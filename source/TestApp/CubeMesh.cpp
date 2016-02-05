#include "CubeMesh.h"
#include "DirectXRenderer.h"

CubeMesh::CubeMesh(const std::string& meshName, Model* model) :
Mesh(meshName, model)
{

}

CubeMesh::~CubeMesh()
{

}

void CubeMesh::Initialize(DirectXRenderer* renderer)
{
	Vertex* vertices;
	unsigned long* indices;
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;

	mVertexCount = 8;
	mIndexCount = 36;

	vertices = new Vertex[mVertexCount];
	indices = new unsigned long[mIndexCount];

	// left-bottom-front
	vertices[0].position = Vec4(-1.0f, -1.0f, -1.0f, 1.0f);
	vertices[0].color = Vec4(1.0f, 0, 1.0f, 1.0f);

	// left-top-front
	vertices[1].position = Vec4(-1.0f, 1.0f, -1.0f, 1.0f);
	vertices[1].color = Vec4(0.0f, 0, 1.0f, 1.0f);

	// right-top-front
	vertices[2].position = Vec4(1.0f, 1.0f, -1.0f, 1.0f);
	vertices[2].color = Vec4(1.0f, 1.0f, 1.0f, 1.0f);

	// right-bottom-front
	vertices[3].position = Vec4(1.0f, -1.0f, -1.0f, 1.0f);
	vertices[3].color = Vec4(0.0f, 0, 0.0f, 1.0f);

	// left-bottom-back
	vertices[4].position = Vec4(-1.0f, -1.0f, 1.0f, 1.0f);
	vertices[4].color = Vec4(1.0f, 0, 0.0f, 1.0f);

	// left-top-back
	vertices[5].position = Vec4(-1.0f, 1.0f, 1.0f, 1.0f);
	vertices[5].color = Vec4(0.0f, 1.0f, 0.0f, 1.0f);

	// right-top-back
	vertices[6].position = Vec4(1.0f, 1.0f, 1.0f, 1.0f);
	vertices[6].color = Vec4(1.0f, 0, 1.0f, 1.0f);

	// right-bottom-back
	vertices[7].position = Vec4(1.0f, -1.0f, 1.0f, 1.0f);
	vertices[7].color = Vec4(0.0f, 1.0f, 1.0f, 1.0f);

	// Front face
	indices[0] = 0; indices[1] = 1; indices[2] = 2;
	indices[3] = 0; indices[4] = 2; indices[5] = 3;

	// Back face
	indices[6] = 4; indices[7] = 6; indices[8] = 5;
	indices[9] = 4; indices[10] = 7; indices[11] = 6;

	// Left face
	indices[12] = 4; indices[13] = 5; indices[14] = 1;
	indices[15] = 4; indices[16] = 1; indices[17] = 0;

	// Right face
	indices[18] = 3; indices[19] = 2; indices[20] = 6;
	indices[21] = 3; indices[22] = 6; indices[23] = 7;

	// Top face
	indices[24] = 1; indices[25] = 5; indices[26] = 6;
	indices[27] = 1; indices[28] = 6; indices[29] = 2;

	// Bottom Face
	indices[30] = 4; indices[31] = 0; indices[32] = 3;
	indices[33] = 4; indices[34] = 3; indices[35] = 7;

	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(Vertex) * mVertexCount;
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

const unsigned int CubeMesh::VertexSize() const
{
	return sizeof(Vertex);
}