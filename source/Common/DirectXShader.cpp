#include "DirectXShader.h"
#include "Common.h"
#include <fstream>
using namespace RenderCore;

DirectXShader::DirectXShader(const std::string& shaderName) : 
Shader(shaderName), 
mVertexShader(nullptr), 
mPixelShader(nullptr), 
mInputLayout(nullptr)
{

}

DirectXShader::~DirectXShader()
{
	RELEASEOBJECT(mVertexShader);
	RELEASEOBJECT(mPixelShader);
	RELEASEOBJECT(mInputLayout);
}

void DirectXShader::Initialize(const std::string& vsFileName, const std::string& psFileName, DirectXRenderer* renderer)
{
	std::ifstream shaderFileStream;

	shaderFileStream.open(vsFileName.c_str(), std::ifstream::in | std::ifstream::binary);
	if (shaderFileStream.good())
	{
		shaderFileStream.seekg(0, std::ios::end);
		mVertexShaderFileSize = (unsigned int)shaderFileStream.tellg();
		mVertexShaderByteCode = new char[mVertexShaderFileSize];
		shaderFileStream.seekg(0, std::ios::beg);
		shaderFileStream.read(mVertexShaderByteCode, mVertexShaderFileSize);
		shaderFileStream.close();

		renderer->Direct3DDevice()->CreateVertexShader(mVertexShaderByteCode, mVertexShaderFileSize, nullptr, &mVertexShader);
	}

	shaderFileStream.open(psFileName.c_str(), std::ifstream::in | std::ifstream::binary);
	if (shaderFileStream.good())
	{
		shaderFileStream.seekg(0, std::ios::end);
		mPixelShaderFileSize = (unsigned int)shaderFileStream.tellg();
		mPixelShaderByteCode = new char[mPixelShaderFileSize];
		shaderFileStream.seekg(0, std::ios::beg);
		shaderFileStream.read(mPixelShaderByteCode, mPixelShaderFileSize);
		shaderFileStream.close();

		renderer->Direct3DDevice()->CreatePixelShader(mPixelShaderByteCode, mPixelShaderFileSize, nullptr, &mPixelShader);
	}
}

void DirectXShader::SetActiveShader(ID3D11DeviceContext* deviceContext)
{
	deviceContext->VSSetShader(mVertexShader, nullptr, 0);
	deviceContext->PSSetShader(mPixelShader, nullptr, 0);
}

void DirectXShader::SetPerFrameBuffer(ID3D11DeviceContext* deviceContext, Camera* camera)
{

}

void DirectXShader::Update(const Core::GameTime& gameTime)
{
	Shader::Update(gameTime);
}