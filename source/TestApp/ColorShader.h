#ifndef COLORSHADER_H 
#define COLORSHADER_H

#include "DirectXShader.h"

class ColorShader : public DirectXShader
{
public:
	ColorShader(const std::string& shaderName);
	virtual ~ColorShader();

	virtual void Update(const GameTime& gameTime);
	virtual void Initialize(const std::string& vsFileName, const std::string& psFileName, DirectXRenderer* renderer);
	virtual void SetActiveShader(ID3D11DeviceContext* deviceContext);
	virtual void SetPerFrameBuffer(ID3D11DeviceContext* deviceContext, Camera* camera);
	virtual void SetPerInstanceBuffer(ID3D11DeviceContext* deviceContext, Renderable* renderable);

private:
	struct PerFrameBuffer
	{
		Mat4x4 view;
		Mat4x4 projection;
	};

	struct PerInstanceBuffer
	{
		Mat4x4 world;
	};
};
#endif