#ifndef DIRECTXSHADER_H
#define DIRECTXSHADER_H

#include <d3d11_1.h>
#include <string>
#include "DirectXRenderer.h"
#include "Camera.h"
#include "GameTime.h"
#include "Shader.h"
using namespace RenderCore;

namespace RenderCore
{
	//Class that defines a shader program
	class DirectXShader : public Shader
	{
	public:
		DirectXShader(const std::string& shaderName);
		virtual ~DirectXShader();

		virtual void Initialize(const std::string& vsFileName, const std::string& psFileName, DirectXRenderer* renderer) = 0;
		virtual void SetActiveShader(ID3D11DeviceContext* deviceContext) = 0;

		virtual void Update(const Core::GameTime& gameTime) = 0;
		virtual void SetPerFrameBuffer(ID3D11DeviceContext* deviceContext, Camera* camera);
		virtual void SetPerInstanceBuffer(ID3D11DeviceContext* deviceContext, Renderable* renderable);

	protected:
		ID3D11VertexShader* mVertexShader;
		ID3D11PixelShader* mPixelShader;
		ID3D11InputLayout *mInputLayout;
		ID3D11Buffer* mPerFrameBuffer;
		ID3D11Buffer* mPerInstanceBuffer;
	};
}
#endif