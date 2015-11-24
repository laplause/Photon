#include "Shader.h"
#include "Common.h"
#include <fstream>
using namespace RenderCore;

Shader::Shader(const std::string& shaderName) : 
mName(shaderName), 
mVertexShaderByteCode(nullptr), 
mPixelShaderByteCode(nullptr),
mVertexShaderFileSize(0), 
mPixelShaderFileSize(0)
{

}

Shader::~Shader()
{
	DELETEOBJECTS(mVertexShaderByteCode);
	DELETEOBJECTS(mPixelShaderByteCode);
}

void Shader::Update(const Core::GameTime& gameTime)
{

}

const std::string& Shader::ShaderName() const
{
	return mName;
}