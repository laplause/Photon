#ifndef CUBEMESH_H
#define CUBEMESH_H

#include "Mesh.h"
#include "PMath.h"
using namespace RenderCore;
using namespace PMath;

class CubeMesh : public Mesh
{
public:
	struct Vertex
	{
		Vec4 position;
		Vec4 color;
	};

	CubeMesh(const std::string& meshName);
	virtual ~CubeMesh();

	virtual void Initialize(DirectXRenderer* renderer);
	virtual const unsigned int VertexSize() const;
};
#endif