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
	polygonLayout[0].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
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

	D3D11_BUFFER_DESC perFrameBufferDesc, perInstanceBufferDesc;
	perFrameBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	perFrameBufferDesc.ByteWidth = sizeof(PerFrameBuffer);
	perFrameBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	perFrameBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	perFrameBufferDesc.MiscFlags = 0;
	perFrameBufferDesc.StructureByteStride = 0;

	perInstanceBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	perInstanceBufferDesc.ByteWidth = sizeof(PerInstanceBuffer);
	perInstanceBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	perInstanceBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	perInstanceBufferDesc.MiscFlags = 0;
	perInstanceBufferDesc.StructureByteStride = 0;

	renderer->Direct3DDevice()->CreateBuffer(&perFrameBufferDesc, nullptr, &mPerFrameBuffer);
	renderer->Direct3DDevice()->CreateBuffer(&perInstanceBufferDesc, nullptr, &mPerInstanceBuffer);
}

void ColorShader::SetActiveShader(ID3D11DeviceContext* deviceContext)
{
	deviceContext->IASetInputLayout(mInputLayout);
	DirectXShader::SetActiveShader(deviceContext);
}

void ColorShader::SetPerFrameBuffer(ID3D11DeviceContext* deviceContext, Camera* camera)
{
	DirectXShader::SetPerFrameBuffer(deviceContext, camera);

	D3D11_MAPPED_SUBRESOURCE mappedResource;
	PerFrameBuffer* perFrameData;
	unsigned int bufferNumber;

	deviceContext->Map(mPerFrameBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	perFrameData = (PerFrameBuffer*)mappedResource.pData;

	perFrameData->view = camera->ViewMatrix();
	perFrameData->projection = camera->ProjectionMatrix();

	deviceContext->Unmap(mPerFrameBuffer, 0);

	bufferNumber = 0;

	deviceContext->VSSetConstantBuffers(bufferNumber, 1, &mPerFrameBuffer);
}

void ColorShader::SetPerInstanceBuffer(ID3D11DeviceContext* deviceContext, Renderable* renderable)
{
	DirectXShader::SetPerInstanceBuffer(deviceContext, renderable);

	D3D11_MAPPED_SUBRESOURCE mappedResource;
	PerInstanceBuffer* perInstanceData;
	unsigned int bufferNumber;

	deviceContext->Map(mPerInstanceBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	perInstanceData = (PerInstanceBuffer*)mappedResource.pData;

	perInstanceData->world = renderable->GetTransform();

	deviceContext->Unmap(mPerInstanceBuffer, 0);

	bufferNumber = 1;

	deviceContext->VSSetConstantBuffers(bufferNumber, 1, &mPerInstanceBuffer);
}