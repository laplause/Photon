#ifndef MESH_H
#define MESH_H

#include <string>
#include <d3d11_1.h>

namespace RenderCore
{
	class DirectXRenderer;

	class Mesh
	{
	public:
		Mesh(const std::string& meshName);
		virtual ~Mesh();

		virtual void Initialize(DirectXRenderer* renderer) = 0;
		virtual const unsigned int VertexSize() const = 0;

		const std::string& MeshName() const;
		ID3D11Buffer* GetVertexBuffer() const;
		ID3D11Buffer* GetIndexBuffer() const;

	protected:
		std::string mName;
		ID3D11Buffer* mVertexBuffer;
		ID3D11Buffer* mIndexBuffer;
		int mVertexCount;
		int mIndexCount;
	};
}
#endif