#include "DirectXRenderer.h"
#include "GameTime.h"
#include "ColorShader.h"
#include "ColorMaterial.h"
#include "TriangleMesh.h"
#include "CubeMesh.h"
#include "Model.h"

int WINAPI WinMain(HINSTANCE instance, HINSTANCE previousInstance, LPSTR commandLine, int showCommand)
{
	GameTime gameTime;
	DirectXRenderer dx(instance, L"RenderWindow", L"blah", showCommand);
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

	Model* m = new Model("Cube");
	m->AddMesh(c);

	Model* mt = new Model("Triangle");
	mt->AddMesh(tm);

	GameObject* go = new GameObject("Cube1");
	GameObject* got = new GameObject("Triangle");
	GameObject* go2 = new GameObject("Cube2");

	Renderable *r = new Renderable(m, go);
	r->SetPosition(5.0f, 0, 0.0f);
	Renderable* offsetR = new Renderable(m, go2);
	offsetR->SetPosition(-5.0f, 0, 0);
	Renderable* t = new Renderable(mt, got);

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