#ifndef INPUT_H
#define INPUT_H

#include "Keyboard.h"
#include "Mouse.h"

class GameObjectCommand;

class Input
{
public:
	Input(const Renderer& renderer);
	~Input();

	enum MouseFeature
	{
		XMOVEMENT = 0,
		YMOVEMENT,
		MOUSEFEATUREMAX
	};

	void Update(const GameTime& gameTime);
	void SetCommand(GameObjectCommand* command, unsigned char key);
	void SetCommand(GameObjectCommand* command, const MouseFeature mouseFeature);

	GameObjectCommand* HandleInput() const;


	//Keyboard Interface
	bool IsKeyUp(unsigned char key) const;
	bool IsKeyDown(unsigned char key) const;
	bool WasKeyUp(unsigned char key) const;
	bool WasKeyDown(unsigned char key) const;
	bool WasKeyPressedThisFrame(unsigned char key) const;
	bool WasKeyReleasedThisFrame(unsigned char key) const;
	bool IsKeyHeldDown(unsigned char key) const;

	//Mouse Interface
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
	Input();
	Input(const Input& rhs);
	Input& operator=(const Input& rhs);

	void Initialize(const Renderer& renderer);

	LPDIRECTINPUT8 mDirectInput;
	Keyboard* mKeyboard;
	Mouse* mMouse;

	// Commands
	GameObjectCommand* mButtonW;
	GameObjectCommand* mButtonS;
	GameObjectCommand* mMouseX;
	GameObjectCommand* mMouseY;
};
#endif