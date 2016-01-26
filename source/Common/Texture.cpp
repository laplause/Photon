#include "Texture.h"
#include "PAssert.h"
#include "Common.h"
#include <WICTextureLoader.h>

Texture::Texture() : mTexture(nullptr)
{

}

Texture::~Texture()
{
	RELEASEOBJECT(mTexture);
}

bool Texture::LoadTexture(const std::wstring& fileName, ID3D11Device* device)
{
	DirectX::CreateWICTextureFromFile(device, fileName.c_str(), nullptr, &mTexture);

	if (mTexture != nullptr)
	{
		ID3D11Resource* res = nullptr;
		ID3D11Texture2D* texture2d = nullptr;
		D3D11_TEXTURE2D_DESC desc;

		mTexture->GetResource(&res);
		res->QueryInterface(&texture2d);
		texture2d->GetDesc(&desc);
		mTextureDimensions.x = (float)desc.Width;
		mTextureDimensions.y = (float)desc.Height;

		RELEASEOBJECT(res);
		RELEASEOBJECT(texture2d);

		return true;
	}

	return false;
}

ID3D11ShaderResourceView* Texture::GetTextureResource() const
{
	ASSERT(mTexture != nullptr, "The texture resource requested has not been loaded.");
	return mTexture;
}

const Vec2& Texture::GetTextureDimensions() const
{
	return mTextureDimensions;
}

const std::string& Texture::TextureName() const
{
	return mName;
}