#ifndef SHADER_H
#define SHADER_H

#include <d3d11_1.h>
#include <string>
#include "Camera.h"
#include "GameTime.h"
#include "DirectXRenderer.h"

namespace RenderCore
{
	//Class that defines a shader program
	class Shader
	{
	public:
		Shader(const std::string& shaderName);
		virtual ~Shader();

		virtual void Update(const Core::GameTime& gameTime) = 0;

		const std::string& ShaderName() const;

	protected:
		char* mVertexShaderByteCode;
		char* mPixelShaderByteCode;
		unsigned int mVertexShaderFileSize;
		unsigned int mPixelShaderFileSize;

	private:
		std::string mName;
	};
}
#endif