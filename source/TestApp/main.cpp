#include "DirectXRenderer.h"
#include "GameTime.h"
#include "ColorShader.h"
#include "ColorMaterial.h"
#include "TriangleMesh.h"
#include "CubeMesh.h"
#include "Model.h"
#include "Input.h"
#include "ServiceLocator.h"
#include "MoveForward.h"
#include "MoveBackward.h"
#include "RotateLeftOrRight.h"

int WINAPI WinMain(HINSTANCE instance, HINSTANCE previousInstance, LPSTR commandLine, int showCommand)
{
	GameTime gameTime;
	ServiceLocator::Provide(&gameTime);

	DirectXRenderer dx(instance, L"RenderWindow", L"blah", showCommand);
	dx.Initialize();

	Input input(dx);
	ServiceLocator::Provide(&input);

	input.SetCommand(new MoveForward(), DIK_W);
	input.SetCommand(new MoveBackward(), DIK_S);
	input.SetCommand(new RotateLeftOrRight(), Input::MouseFeature::XMOVEMENT);

	ColorShader* cs = new ColorShader("ColorShader");
	cs->Initialize("..//..//bin//ColorVS.cso", "..//..//bin//ColorPS.cso", &dx);

	ColorMaterial* cm = new ColorMaterial("ColorMaterial", nullptr);
	cm->Initialize();

	dx.AddShader(cs);
	dx.LinkMaterialToShader(cs, cm);

	Model* mt = new Model("Triangle");
	Model* m = new Model("Cube");

	TriangleMesh* tm = new TriangleMesh("Triangle", mt);
	tm->Initialize(&dx);

	CubeMesh* c = new CubeMesh("Cube", m);
	c->Initialize(&dx);

	dx.LinkMeshToMaterial(cm, tm);
	dx.LinkMeshToMaterial(cm, c);

	m->AddMesh(c);
	mt->AddMesh(tm);

	GameObject* go = new GameObject("Cube1");
	GameObject* got = new GameObject("Triangle");
	GameObject* go2 = new GameObject("Cube2");

	Renderable *r = new Renderable(m, go);
	Renderable* offsetR = new Renderable(m, go2);
	Renderable* t = new Renderable(mt, got);

	go->SetPosition(5.0f, 0, 0);
	go2->SetPosition(-5.0f, 0, 0);

	dx.LinkRenderableToModel(m, r);
	dx.LinkRenderableToModel(m, offsetR);
	dx.LinkRenderableToModel(mt, t);

	dx.AddModel(m);
	dx.AddModel(mt);

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
			input.Update(gameTime);

			dx.Update(gameTime);
			dx.Draw(gameTime);
		}
	}

	return 0;
}