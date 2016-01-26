#include "Material.h"
#include "Common.h"

Material::Material(const std::string& materialName, Texture* texture) :
mName(materialName), 
mTexture(texture),
mColor(nullptr)
{

}

Material::~Material()
{
	DELETEOBJECT(mTexture);
	DELETEOBJECTS(mColor);
}

const Texture* Material::GetTexture() const
{
	return mTexture;
}

const Vec4* Material::GetColor() const
{
	return mColor;
}

const std::string& Material::MaterialName() const
{
	return mName;
}