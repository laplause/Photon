#include "Input.h"
#include "PAssert.h"
#include "Common.h"
#include "Renderer.h"

Input::Input(const Renderer& renderer) :
mDirectInput(nullptr),
mKeyboard(nullptr),
mMouse(nullptr)
{
	DirectInput8Create(renderer.GetWindow()->GetInstance(), DIRECTINPUT_VERSION, IID_IDirectInput8, (LPVOID*)&mDirectInput, nullptr);
	Initialize(renderer);
}

Input::~Input()
{
	if (mKeyboard)
	{
		DELETEOBJECT(mKeyboard);
	}

	if (mMouse)
	{
		DELETEOBJECT(mMouse);
	}
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