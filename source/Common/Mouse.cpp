#include "Mouse.h"
#include "PAssert.h"
#include "Renderer.h"

Mouse::Mouse(const Renderer& renderer, LPDIRECTINPUT8 directInput) :
mDevice(nullptr),
mDirectInput(directInput),
mX(0),
mY(0),
mWheel(0)
{
	ASSERT(mDirectInput != nullptr, "The directInput pointer used to create the object was created unsuccessfully.");
	ZeroMemory(&mCurrentState, sizeof(mCurrentState));
	ZeroMemory(&mLastState, sizeof(mLastState));
	Initialize(renderer);
}

Mouse::~Mouse()
{
	if (mDevice != nullptr)
	{
		mDevice->Unacquire();
		mDevice->Release();
		mDevice = nullptr;
	}
}

void Mouse::Initialize(const Renderer& renderer)
{
	mDirectInput->CreateDevice(GUID_SysMouse, &mDevice, nullptr);
	ASSERT(mDevice != nullptr, "IDIRECTINPUT8::CreateDevice() failed");

	if (FAILED(mDevice->SetDataFormat(&c_dfDIMouse)))
	{
		ASSERT(mDevice == nullptr, "IDirectInputDevice8::SetDataFormat() failed");
	}

	mDevice->SetCooperativeLevel(renderer.GetWindow()->GetWindowHandle(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	mDevice->Acquire();
}

void Mouse::Update(const GameTime& gameTime)
{
	if (mDevice != nullptr)
	{
		memcpy(&mLastState, &mCurrentState, sizeof(mCurrentState));

		if (FAILED(mDevice->GetDeviceState(sizeof(mCurrentState), &mCurrentState)))
		{
			if (SUCCEEDED(mDevice->Acquire()))
			{
				if (FAILED(mDevice->GetDeviceState(sizeof(mCurrentState), &mCurrentState)))
				{
					return;
				}
			}
		}

		mX = mCurrentState.lX;
		mY = mCurrentState.lY;
		mWheel = mCurrentState.lZ;
	}
}

long Mouse::X() const
{
	return mX;
}

long Mouse::Y() const
{
	return mY;
}

long Mouse::Wheel() const
{
	return mWheel;
}

bool Mouse::IsButtonUp(MouseButtons button) const
{
	return ((mCurrentState.rgbButtons[button] & 0x80) == 0);
}

bool Mouse::IsButtonDown(MouseButtons button) const
{
	return ((mCurrentState.rgbButtons[button] & 0x80) != 0);
}

bool Mouse::WasButtonUp(MouseButtons button) const
{
	return ((mLastState.rgbButtons[button] & 0x80) == 0);
}

bool Mouse::WasButtonDown(MouseButtons button) const
{
	return ((mLastState.rgbButtons[button] & 0x80) != 0);
}

bool Mouse::WasButtonPressedThisFrame(MouseButtons button) const
{
	return (IsButtonDown(button) && WasButtonUp(button));
}

bool Mouse::WasButtonReleasedThisFrame(MouseButtons button) const
{
	return (IsButtonUp(button) && WasButtonDown(button));
}

bool Mouse::IsButtonHeldDown(MouseButtons button) const
{
	return (IsButtonDown(button) && WasButtonDown(button));
}