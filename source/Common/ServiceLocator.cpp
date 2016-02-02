#include "ServiceLocator.h"

GameTime* ServiceLocator::mGameTimeService = nullptr;
Input* ServiceLocator::mInput = nullptr;

ServiceLocator::ServiceLocator()
{

}

ServiceLocator::~ServiceLocator()
{

}

void ServiceLocator::Provide(GameTime* gameTime)
{
	mGameTimeService = gameTime;
}

void ServiceLocator::Provide(Input* input)
{
	mInput = input;
}

GameTime* ServiceLocator::GetGameTime()
{
	return mGameTimeService;
}

Input* ServiceLocator::GetInput()
{
	return mInput;
}