#include "ColorShader.h"

ColorShader::ColorShader(const std::string& shaderName) : 
DirectXShader(shaderName)
{

}

ColorShader::~ColorShader()
{

}

void ColorShader::Update(const Core::GameTime& gameTime)
{
	DirectXShader::Update(gameTime);
}

void ColorShader::Initialize(const std::string& vsFileName, const std::string& psFileName, DirectXRenderer* renderer)
{
	DirectXShader::Initialize(vsFileName, psFileName, renderer);

	D3D11_INPUT_ELEMENT_DESC polygonLayout[2];
	unsigned int numElements;

	polygonLayout[0].SemanticName = "POSITION";
	polygonLayout[0].SemanticIndex = 0;
	polygonLayout[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	polygonLayout[0].InputSlot = 0;
	polygonLayout[0].AlignedByteOffset = 0;
	polygonLayout[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	polygonLayout[0].InstanceDataStepRate = 0;

	polygonLayout[1].SemanticName = "COLOR";
	polygonLayout[1].SemanticIndex = 0;
	polygonLayout[1].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	polygonLayout[1].InputSlot = 0;
	polygonLayout[1].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	polygonLayout[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	polygonLayout[1].InstanceDataStepRate = 0;

	numElements = sizeof(polygonLayout) / sizeof(polygonLayout[0]);

	renderer->Direct3DDevice()->CreateInputLayout(polygonLayout, numElements, mVertexShaderByteCode, mVertexShaderFileSize, &mInputLayout);
}

void ColorShader::SetActiveShader(ID3D11DeviceContext* deviceContext)
{
	deviceContext->IASetInputLayout(mInputLayout);
	DirectXShader::SetActiveShader(deviceContext);
}

void ColorShader::SetPerFrameBuffer(ID3D11DeviceContext* deviceContext, Camera* camera)
{
	DirectXShader::SetPerFrameBuffer(deviceContext, camera);
}