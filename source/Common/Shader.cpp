#include "Shader.h"
#include "Common.h"
#include <fstream>

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

void Shader::Update(const GameTime& gameTime)
{

}

const std::string& Shader::ShaderName() const
{
	return mName;
}