#ifndef MATERIAL_H
#define MATERIAL_H

#include <string>
#include "Texture.h"
#include "PMath.h"

namespace RenderCore
{
	//Class that defines the look of a mesh.
	class Material
	{
	public:
		Material(const std::string& materialName, Texture* texture);
		virtual ~Material();

		virtual void Initialize() = 0;

		const Texture* GetTexture() const;
		const PMath::Vec4* GetColor() const;
		const std::string& MaterialName() const;

	protected:
		std::string mName;
		PMath::Vec4* mColor;
		Texture* mTexture;
	};
}
#endif