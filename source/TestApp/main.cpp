#include "DirectXRenderer.h"
#include "GameTime.h"
#include "ColorShader.h"
#include "ColorMaterial.h"
#include "TriangleMesh.h"
#include "Model.h"
using namespace RenderCore;

int WINAPI WinMain(HINSTANCE instance, HINSTANCE previousInstance, LPSTR commandLine, int showCommand)
{
	Core::GameTime gameTime;
	RenderCore::DirectXRenderer dx(instance, L"RenderWindow", L"blah", showCommand);
	dx.Initialize();

	ColorShader* cs = new ColorShader("ColorShader");
	cs->Initialize("..//..//bin//ColorVS.cso", "..//..//bin//ColorPS.cso", &dx);

	ColorMaterial* cm = new ColorMaterial("ColorMaterial", nullptr);
	cm->Initialize();

	dx.AddShader(cs->ShaderName(), cs);
	dx.AddMaterial("ColorMaterial", cm);
	dx.LinkMaterialToShader("ColorShader", "ColorMaterial");

	TriangleMesh* tm = new TriangleMesh("Triangle");
	tm->Initialize(&dx);

	RenderCore::Model* m = new Model("Triangle");
	m->AddMesh(tm);
	dx.AddMesh(tm);

	RenderCore::Renderable* r = new Renderable(m);

	dx.AddModel("Triangle", m);
	dx.AddRenderable(r);
	dx.LinkMeshToMaterial("ColorMaterial", tm);

	MSG message;
	ZeroMemory(&message, sizeof(message));

	while (message.message != WM_QUIT)
	{
		if (PeekMessage(&message, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&message);
			DispatchMessage(&message);
		}
		else
		{
			gameTime.UpdateTime();

			dx.Update(gameTime);
			dx.Draw(gameTime);
		}
	}

	return 0;
}