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

	void AddShader(DirectXShader* shader);
	void AddModel(Model* model);

	void LinkMaterialToShader(DirectXShader* shader, Material* material);
	void LinkMeshToMaterial(Material* material, Mesh* mesh);
	void LinkRenderableToModel(Model* model, Renderable* renderable);

	const SystemWindow* GetWindow() const;

protected:
	std::vector<DirectXShader*> mShaderList;
	std::vector<Model*> mModelList;

	std::map<DirectXShader*, std::vector<Material*> > mShaderToMaterialMap;
	std::map<Material*, std::vector<Mesh*> > mMaterialToMeshMap;
	std::map<Model*, std::vector<Renderable*> > mModelToRenderableMap;

	SystemWindow* mWindow;
	unsigned int mScreenWidth;
	unsigned int mScreeHeight;
	bool mIsFullScreen;
};
#endif