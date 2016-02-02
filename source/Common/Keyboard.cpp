#include "Keyboard.h"
#include "PAssert.h"
#include "Renderer.h"

Keyboard::Keyboard(const Renderer& renderer, LPDIRECTINPUT8 directInput) :
mDevice(nullptr),
mDirectInput(directInput)
{
	ASSERT(mDirectInput != nullptr, "The directInput pointer used to create the object was created unsuccessfully.");
	ZeroMemory(mCurrentState, sizeof(mCurrentState));
	ZeroMemory(mLastState, sizeof(mLastState));
	Initialize(renderer);
}

Keyboard::~Keyboard()
{
	if (mDevice != nullptr)
	{
		mDevice->Unacquire();
		mDevice->Release();
		mDevice = nullptr;
	}
}

void Keyboard::Initialize(const Renderer& renderer)
{
	mDirectInput->CreateDevice(GUID_SysKeyboard, &mDevice, nullptr);
	ASSERT(mDevice != nullptr, "IDIRECTINPUT8::CreateDevice() failed");

	if (FAILED(mDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		ASSERT(mDevice == nullptr, "IDirectInputDevice8::SetDataFormat() failed");
	}

	mDevice->SetCooperativeLevel(renderer.GetWindow()->GetWindowHandle(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	mDevice->Acquire();
}

void Keyboard::Update(const GameTime& gameTime)
{
	if (mDevice != nullptr)
	{
		memcpy(mLastState, mCurrentState, sizeof(mCurrentState));

		if (FAILED(mDevice->GetDeviceState(sizeof(mCurrentState), (LPVOID)mCurrentState)))
		{
			if (SUCCEEDED(mDevice->Acquire()))
			{
				mDevice->GetDeviceState(sizeof(mCurrentState), (LPVOID)mCurrentState);
			}
		}
	}
}

bool Keyboard::IsKeyUp(unsigned char key) const
{
	return ((mCurrentState[key] & 0x80) == 0);
}

bool Keyboard::IsKeyDown(unsigned char key) const
{
	return ((mCurrentState[key] & 0x80) != 0);
}

bool Keyboard::WasKeyUp(unsigned char key) const
{
	return ((mLastState[key] & 0x80) == 0);
}

bool Keyboard::WasKeyDown(unsigned char key) const
{
	return ((mLastState[key] & 0x80) != 0);
}

bool Keyboard::WasKeyPressedThisFrame(unsigned char key) const
{
	return (IsKeyDown(key) && WasKeyUp(key));
}

bool Keyboard::WasKeyReleasedThisFrame(unsigned char key) const
{
	return (IsKeyUp(key) && WasKeyDown(key));
}

bool Keyboard::IsKeyHeldDown(unsigned char key) const
{
	return (IsKeyDown(key) && WasKeyDown(key));
}