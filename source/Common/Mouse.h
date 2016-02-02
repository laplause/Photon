#ifndef MOUSE_H
#define MOUSE_H

#include <dinput.h>

class Renderer;
class GameTime;

enum MouseButtons
{
	MOUSEBUTTONSLEFT = 0,
	MOUSEBUTTONSRIGHT = 1,
	MOUSEBUTTONSMIDDLE = 2,
	MOUSEBUTTONSX1 = 3,
	MOUSEBUTTONSMAX
};

class Mouse
{
public:
	Mouse(const Renderer& renderer, LPDIRECTINPUT8 directInput);
	~Mouse();

	void Update(const GameTime& gameTime);

	long X() const;
	long Y() const;
	long Wheel() const;

	bool IsButtonUp(MouseButtons button) const;
	bool IsButtonDown(MouseButtons button) const;
	bool WasButtonUp(MouseButtons button) const;
	bool WasButtonDown(MouseButtons button) const;
	bool WasButtonPressedThisFrame(MouseButtons button) const;
	bool WasButtonReleasedThisFrame(MouseButtons button) const;
	bool IsButtonHeldDown(MouseButtons button) const;

private:
	Mouse();
	Mouse(const Mouse& rhs);
	void Initialize(const Renderer& renderer);

	LPDIRECTINPUT8 mDirectInput;
	LPDIRECTINPUTDEVICE8 mDevice;
	DIMOUSESTATE mCurrentState;
	DIMOUSESTATE mLastState;

	long mX;
	long mY;
	long mWheel;
};
#endif