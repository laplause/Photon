#ifndef RENDERER_H
#define RENDERER_H

#include "SystemWindow.h"
#include "System.h"
#include "Material.h"
#include "Renderable.h"
#include "Model.h"
#include <vector>
#include <map>
#include <string>

using namespace Core;
using namespace RenderCore;

namespace RenderCore
{
	class DirectXShader;

	//Abstract base class that defines the essentials of a renderer.
	class Renderer : public System
	{
	public:
		Renderer();
#ifdef WINDOWS
		Renderer(HINSTANCE instance, const std::wstring& windowClass, const std::wstring& windowTitle, int showCommand);
#endif
		virtual ~Renderer();

		virtual void Draw(const GameTime& gameTime) = 0;

		virtual void Initialize();
		virtual void Shutdown();
		virtual void Update(const GameTime& gameTime);

		void AddShader(const std::string& shaderName, DirectXShader* shader);
		void AddMaterial(const std::string& materialName, Material* material);
		void AddModel(const std::string& modelName, Model* model);
		void AddMesh(Mesh* mesh);
		void AddRenderable(Renderable* renderable);

		Material* GetMaterial(const std::string& materialName);
		DirectXShader* GetShader(const std::string& shaderName);
		Model* GetModel(const std::string& modelName);

		void LinkMaterialToShader(const std::string& shaderName, const std::string& materialName);
		void LinkMaterialToShader(const std::string& shaderName, Material* material);
		void LinkMeshToMaterial(const std::string& materialName, Mesh* mesh);

		const SystemWindow* GetWindow() const;

	protected:
		std::map<std::string, DirectXShader*> mShaderTable;
		std::map<std::string, Material*> mMaterialTable;
		std::map<std::string, Model*> mModelTable;
		std::vector<Mesh*> mMeshList;
		std::vector<Renderable*> mRenderableList;
		std::map<std::string, std::vector<Material*> > mShaderIndexToMaterialMap;
		std::map<std::string, std::vector<Mesh*> > mMaterialIndexToMeshMap;
		SystemWindow* mWindow;
		unsigned int mScreenWidth;
		unsigned int mScreeHeight;
		bool mIsFullScreen;
	};
}
#endif