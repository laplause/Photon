#ifndef TRIANGLEMESH_H
#define TRIANGLEMESH_H

#include "Mesh.h"
#include "PMath.h"

class TriangleMesh : public Mesh
{
public:
	struct Vertex
	{
		Vec4 position;
		Vec4 color;
	};

	TriangleMesh(const std::string& meshName);
	virtual ~TriangleMesh();

	virtual void Initialize(DirectXRenderer* renderer);
	virtual const unsigned int VertexSize() const;
};
#endif