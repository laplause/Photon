#ifndef SERVICELOCATOR_H
#define SERVICELOCATOR_H

class GameTime;
class Input;

class ServiceLocator
{
public:
	ServiceLocator();
	~ServiceLocator();

	static GameTime* GetGameTime();
	static void Provide(GameTime* gameTime);

	static Input* GetInput();
	static void Provide(Input* input);

private:
	static GameTime* mGameTimeService;
	static Input* mInput;
};
#endif