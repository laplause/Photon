#ifndef COLORSHADER_H 
#define COLORSHADER_H

#include "DirectXShader.h"
using namespace RenderCore;

class ColorShader : public DirectXShader
{
public:
	ColorShader(const std::string& shaderName);
	virtual ~ColorShader();

	virtual void Update(const Core::GameTime& gameTime);
	virtual void Initialize(const std::string& vsFileName, const std::string& psFileName, DirectXRenderer* renderer);
	virtual void SetActiveShader(ID3D11DeviceContext* deviceContext);
	virtual void SetPerFrameBuffer(ID3D11DeviceContext* deviceContext, Camera* camera);
};
#endif