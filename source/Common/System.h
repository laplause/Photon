#ifndef SYSTEM_H
#define SYSTEM_H

#include "GameTime.h"

//Abstract base class that defines a zephyr system.
class System
{
public:
	System();
	virtual ~System();

	virtual void Initialize() = 0;
	virtual void Shutdown() = 0;
	virtual void Update(const GameTime& gameTime) = 0;
};
#endif