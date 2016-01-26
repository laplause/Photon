#ifndef TEXTURE_H
#define TEXTURE_H

#include <d3d11.h>
#include <string>
#include "PMath.h"

//Class that defines a Texture being used by the engine
class Texture
{
public:
	Texture();
	~Texture();

	bool LoadTexture(const std::wstring& fileName, ID3D11Device* device);
	ID3D11ShaderResourceView* GetTextureResource() const;
	const Vec2& GetTextureDimensions() const;

	const std::string& TextureName() const;

private:
	std::string mName;
	ID3D11ShaderResourceView* mTexture;
	Vec2 mTextureDimensions;
};
#endif