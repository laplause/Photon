#include "Renderer.h"
#include "Common.h"
#include "DirectXShader.h"

Renderer::Renderer() : 
mShaderList(),
mModelList(),
mShaderToMaterialMap(),
mMaterialToMeshMap(),
mModelToRenderableMap(),
mWindow(nullptr),
mScreenWidth(800),
mScreeHeight(600),
mIsFullScreen(false)
{

}

Renderer::Renderer(HINSTANCE instance, const std::wstring& windowClass, const std::wstring& windowTitle, int showCommand) :
mShaderList(),
mModelList(),
mShaderToMaterialMap(),
mMaterialToMeshMap(),
mModelToRenderableMap(),
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

void Renderer::AddShader(DirectXShader* shader)
{
	ASSERT(shader != nullptr, "Tried to add a null shader");

	mShaderList.push_back(shader);
}

void Renderer::AddModel(Model* model)
{
	ASSERT(model != nullptr, "Trying to add a null model");

	mModelList.push_back(model);
}

void Renderer::LinkMaterialToShader(DirectXShader* shader, Material* material)
{
	ASSERT(material != nullptr, "Cannot link using null material");
	ASSERT(shader != nullptr, "Cannot link using null shader");

	mShaderToMaterialMap[shader].push_back(material);
}

void Renderer::LinkMeshToMaterial(Material* material, Mesh* mesh)
{
	ASSERT(material != nullptr, "Cannot link using a null material");
	ASSERT(mesh != nullptr, "Cannot link using a null mesh");

	mMaterialToMeshMap[material].push_back(mesh);
}

void Renderer::LinkRenderableToModel(Model* model, Renderable* renderable)
{
	ASSERT(renderable != nullptr, "Cannot link using null renderable");
	ASSERT(model != nullptr, "Cannot link using null model");

	mModelToRenderableMap[model].push_back(renderable);
}

void Renderer::Shutdown()
{
	DELETEOBJECT(mWindow);
}