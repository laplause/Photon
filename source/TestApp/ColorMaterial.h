#ifndef COLORMATERIAL_H
#define COLORMATERIAL_H

#include "Material.h"
using namespace RenderCore;
using namespace PMath;

class ColorMaterial : public Material
{
public:
	ColorMaterial(const std::string& materialName, Texture* texture);
	virtual ~ColorMaterial();

	virtual void Initialize();
};

#endif