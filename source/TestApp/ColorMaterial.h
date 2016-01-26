#ifndef COLORMATERIAL_H
#define COLORMATERIAL_H

#include "Material.h"

class ColorMaterial : public Material
{
public:
	ColorMaterial(const std::string& materialName, Texture* texture);
	virtual ~ColorMaterial();

	virtual void Initialize();
};

#endif