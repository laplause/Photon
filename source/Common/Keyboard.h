#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <dinput.h>

class Renderer;
class GameTime;

class Keyboard
{
public:
	Keyboard(const Renderer& renderer, LPDIRECTINPUT8 directInput);
	~Keyboard();

	void Update(const GameTime& gameTime);

	bool IsKeyUp(unsigned char key) const;
	bool IsKeyDown(unsigned char key) const;
	bool WasKeyUp(unsigned char key) const;
	bool WasKeyDown(unsigned char key) const;
	bool WasKeyPressedThisFrame(unsigned char key) const;
	bool WasKeyReleasedThisFrame(unsigned char key) const;
	bool IsKeyHeldDown(unsigned char key) const;

private:
	Keyboard(const Keyboard& rhs);
	void Initialize(const Renderer& renderer);

	static const int KeyCount = 256;

	LPDIRECTINPUT8 mDirectInput;
	LPDIRECTINPUTDEVICE8 mDevice;
	unsigned char mCurrentState[KeyCount];
	unsigned char mLastState[KeyCount];
};
#endif