#ifndef GAMETIME_H
#define GAMETIME_H

#include "EngineState.h"

#ifdef WINDOWS
#include <windows.h>
#endif

namespace Core
{
	class GameTime
	{
	public:
		GameTime();

		double TotalGameTime() const;
		double DeltaTime() const;

		void UpdateTime();
		void Reset();

	private:
		GameTime(const GameTime& rhs);
		GameTime& operator=(const GameTime& rhs);

		const double GetFrequency();

		double mFrquency;
		double mTotalGameTime;
		double mDeltaTime;;

#ifdef WINDOWS
		LARGE_INTEGER mStartTime;
		LARGE_INTEGER mCurrentTime;
		LARGE_INTEGER mLastTime;
#endif
	};
}
#endif