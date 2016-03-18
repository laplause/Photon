#include "Input.h"
#include "PAssert.h"
#include "Common.h"
#include "Renderer.h"

Input::Input(const Renderer& renderer) :
mDirectInput(nullptr),
mKeyboard(nullptr),
mMouse(nullptr),
mButtonW(nullptr),
mButtonS(nullptr),
mCommandList(20)
{
	DirectInput8Create(renderer.GetWindow()->GetInstance(), DIRECTINPUT_VERSION, IID_IDirectInput8, (LPVOID*)&mDirectInput, nullptr);
	Initialize(renderer);
}

Input::~Input()
{
	DELETEOBJECT(mKeyboard);
	DELETEOBJECT(mMouse);
	DELETEOBJECT(mButtonW);
	DELETEOBJECT(mButtonS);
	DELETEOBJECT(mButtonA);
	DELETEOBJECT(mButtonD);
}

void Input::Initialize(const Renderer& renderer)
{
	mKeyboard = new Keyboard(renderer, mDirectInput);
	mMouse = new Mouse(renderer, mDirectInput);
}

void Input::Update(const GameTime& gameTime)
{
	mKeyboard->Update(gameTime);
	mMouse->Update(gameTime);
	mCommandList.clear();
}

const std::vector<GameObjectCommand*>& Input::HandleInput()
{
	if (IsKeyDown(DIK_W)) mCommandList.push_back(mButtonW);
	if (IsKeyDown(DIK_S)) mCommandList.push_back(mButtonS);
	if (IsKeyDown(DIK_A)) mCommandList.push_back(mButtonA);
	if (IsKeyDown(DIK_D)) mCommandList.push_back(mButtonD);

	return mCommandList;
}

void Input::SetCommand(GameObjectCommand* command, unsigned char key)
{
	if (command != nullptr)
	{
		if (key == DIK_W)
		{
			mButtonW = command;
		}
		else if (key == DIK_S)
		{
			mButtonS = command;
		}
		else if (key == DIK_A)
		{
			mButtonA = command;
		}
		else if (key == DIK_D)
		{
			mButtonD = command;
		}
	}
}

bool Input::IsKeyUp(unsigned char key) const
{
	return mKeyboard->IsKeyUp(key);
}

bool Input::IsKeyDown(unsigned char key) const
{
	return mKeyboard->IsKeyDown(key);
}

bool Input::WasKeyUp(unsigned char key) const
{
	return mKeyboard->WasKeyUp(key);
}

bool Input::WasKeyDown(unsigned char key) const
{
	return mKeyboard->WasKeyDown(key);
}

bool Input::WasKeyPressedThisFrame(unsigned char key) const
{
	return mKeyboard->WasKeyPressedThisFrame(key);
}

bool Input::WasKeyReleasedThisFrame(unsigned char key) const
{
	return mKeyboard->WasKeyReleasedThisFrame(key);
}

bool Input::IsKeyHeldDown(unsigned char key) const
{
	return mKeyboard->IsKeyHeldDown(key);
}

long Input::X() const
{
	return mMouse->X();
}

long Input::Y() const
{
	return mMouse->Y();
}

long Input::Wheel() const
{
	return mMouse->Wheel();
}

bool Input::IsButtonUp(MouseButtons button) const
{
	return mMouse->IsButtonUp(button);
}

bool Input::IsButtonDown(MouseButtons button) const
{
	return mMouse->IsButtonDown(button);
}

bool Input::WasButtonUp(MouseButtons button) const
{
	return mMouse->WasButtonUp(button);
}

bool Input::WasButtonDown(MouseButtons button) const
{
	return mMouse->WasButtonDown(button);
}

bool Input::WasButtonPressedThisFrame(MouseButtons button) const
{
	return mMouse->WasButtonPressedThisFrame(button);
}

bool Input::WasButtonReleasedThisFrame(MouseButtons button) const
{
	return mMouse->WasButtonReleasedThisFrame(button);
}

bool Input::IsButtonHeldDown(MouseButtons button) const
{
	return mMouse->IsButtonHeldDown(button);
}