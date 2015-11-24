#include "ColorMaterial.h"

ColorMaterial::ColorMaterial(const std::string& materialName, Texture* texture) :
Material(materialName, texture)
{

}

ColorMaterial::~ColorMaterial()
{

}

void ColorMaterial::Initialize()
{
	mColor = new Vec4[3];
	mColor[0] = Vec4(1.0f, 0, 0, 1.0f);
	mColor[1] = Vec4(0, 1.0f, 0, 1.0f);
	mColor[2] = Vec4(0, 0, 1.0f, 1.0f);
}