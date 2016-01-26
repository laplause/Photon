#include "GameTime.h"
#include "PAssert.h"

GameTime::GameTime() : mTotalGameTime(0), mDeltaTime(0), mStartTime(), mCurrentTime(), mLastTime(), mFrquency()
{
	mFrquency = GetFrequency();
	Reset();
}

double GameTime::TotalGameTime() const
{
	return mTotalGameTime;
}

double GameTime::DeltaTime() const
{
	return mDeltaTime;
}

void GameTime::UpdateTime()
{
	QueryPerformanceFrequency(&mCurrentTime);
	mTotalGameTime = (mCurrentTime.QuadPart - mStartTime.QuadPart) / mFrquency;
	mDeltaTime = (mCurrentTime.QuadPart - mLastTime.QuadPart) / mFrquency;
	mLastTime = mCurrentTime;
}

const double GameTime::GetFrequency()
{
	LARGE_INTEGER frequency;
	ASSERT(QueryPerformanceFrequency(&frequency), "The high perfromance frequency counter failed to get the frequency.");
	return (double)frequency.QuadPart;
}

void GameTime::Reset()
{
	QueryPerformanceFrequency(&mStartTime);
	mCurrentTime = mStartTime;
	mLastTime = mCurrentTime;
}