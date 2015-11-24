#include "Renderer.h"
#include "Common.h"
#include "DirectXShader.h"
using namespace RenderCore;

Renderer::Renderer() : 
mShaderTable(),
mMaterialTable(),
mModelTable(),
mRenderableList(),
mShaderIndexToMaterialMap(),
mMaterialIndexToMeshMap(),
mWindow(nullptr),
mScreenWidth(800),
mScreeHeight(600),
mIsFullScreen(false)
{

}

Renderer::Renderer(HINSTANCE instance, const std::wstring& windowClass, const std::wstring& windowTitle, int showCommand) :
mShaderTable(),
mMaterialTable(),
mModelTable(),
mRenderableList(),
mShaderIndexToMaterialMap(),
mMaterialIndexToMeshMap(),
mWindow(nullptr),
mScreenWidth(800),
mScreeHeight(600),
mIsFullScreen(false)
{
	mWindow = new SystemWindow(instance, windowClass, windowTitle, showCommand);
	mScreenWidth = mWindow->ScreenWidth();
	mScreeHeight = mWindow->ScreenHeight();
	mIsFullScreen = mWindow->IsFullScreen();
}

Renderer::~Renderer()
{
	Shutdown();
}

void Renderer::Initialize()
{
	mWindow->Initialize();
}

void Renderer::Update(const GameTime& gameTime)
{

}

void Renderer::Draw(const GameTime& gameTime)
{

}

const SystemWindow* Renderer::GetWindow() const
{
	return mWindow;
}

void Renderer::AddShader(const std::string& shaderName, DirectXShader* shader)
{
	ASSERT(shaderName != "", "Trying to add a shader with no name");
	ASSERT(shader != nullptr, "Tried to add a null shader");

	mShaderTable[shaderName] = shader;
}

void Renderer::AddMaterial(const std::string& materialName, Material* material)
{
	ASSERT(materialName != "", "Trying to add a material with no name");
	ASSERT(material != nullptr, "Trying to add a null material");
	
	mMaterialTable[materialName] = material;
}

void Renderer::AddModel(const std::string& modelName, Model* model)
{
	ASSERT(modelName != "", "Trying to add a model with no name");
	ASSERT(model != nullptr, "Trying to add a null model");

	mModelTable[modelName] = model;
}

void Renderer::AddMesh(Mesh* mesh)
{
	ASSERT(mesh != nullptr, "Trying to add a null mesh");

	mMeshList.push_back(mesh);
}

void Renderer::AddRenderable(Renderable* renderable)
{
	ASSERT(renderable != nullptr, "Trying to add a null renderable");

	mRenderableList.push_back(renderable);
}

Material* Renderer::GetMaterial(const std::string& materialName)
{
	return mMaterialTable[materialName];
}

DirectXShader* Renderer::GetShader(const std::string& shaderName)
{
	return mShaderTable[shaderName];
}

Model* Renderer::GetModel(const std::string& modelName)
{
	return mModelTable[modelName];
}

void Renderer::LinkMaterialToShader(const std::string& shaderName, const std::string& materialName)
{
	ASSERT(materialName != "", "Cannot link material with no name to a shader");

	mShaderIndexToMaterialMap[shaderName].push_back(mMaterialTable[materialName]);
}

void Renderer::LinkMaterialToShader(const std::string& shaderName, Material* material)
{
	ASSERT(material != nullptr, "Cannot link null material to a shader");

	mShaderIndexToMaterialMap[shaderName].push_back(material);
}

void Renderer::LinkMeshToMaterial(const std::string& materialName, Mesh* mesh)
{
	ASSERT(mesh != nullptr, "Cannot link null mesh to a material");

	mMaterialIndexToMeshMap[materialName].push_back(mesh);
}

void Renderer::Shutdown()
{
	// Delete Shaders
	for (std::map<std::string, DirectXShader*>::iterator it = mShaderTable.begin(); it != mShaderTable.end(); ++it)
	{
		DELETEOBJECT(it->second);
	}

	// Delete Materials
	for (std::map<std::string, Material*>::iterator it = mMaterialTable.begin(); it != mMaterialTable.end(); ++it)
	{
		DELETEOBJECT(it->second);
	}

	// Delete Models
	for (std::map<std::string, Model*>::iterator it = mModelTable.begin(); it != mModelTable.end(); ++it)
	{
		DELETEOBJECT(it->second);
	}

	// Delete Renderables
	for (std::vector<Renderable*>::iterator it = mRenderableList.begin(); it != mRenderableList.end(); ++it)
	{
		DELETEOBJECT(*it);
	}

	DELETEOBJECT(mWindow);
}