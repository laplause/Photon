#include "DirectXRenderer.h"
#include "GameTime.h"
#include "ColorShader.h"
#include "ColorMaterial.h"
#include "TriangleMesh.h"
#include "CubeMesh.h"
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

	CubeMesh* c = new CubeMesh("Cube");
	c->Initialize(&dx);

	RenderCore::Model* m = new Model("Cube");
	m->AddMesh(c);

	RenderCore::Model* mt = new Model("Triangle");
	mt->AddMesh(tm);

	Renderable *r = new Renderable(m);
	r->SetPosition(5.0f, 0, 0.0f);
	Renderable* offsetR = new Renderable(m);
	offsetR->SetPosition(-5.0f, 0, 0);
	Renderable* t = new Renderable(mt);

	dx.AddModel("Cube", m);
	dx.AddModel("Triangle", mt);

	dx.AddRenderable(r);
	dx.AddRenderable(offsetR);

	dx.LinkRenderableToMaterial("ColorMaterial", r);
	dx.LinkRenderableToMaterial("ColorMaterial", offsetR);
	dx.LinkRenderableToMaterial("ColorMaterial", t);

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