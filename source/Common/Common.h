#ifndef COMMON_H
#define COMMON_H

#include "EngineState.h"
#include "PAssert.h"

#define DELETEOBJECT(object) if((object) != nullptr) {delete object; object = nullptr;}
#define DELETEOBJECTS(objects) if((objects) != nullptr) {delete[] objects; objects = nullptr;}
#define RELEASEOBJECT(object) if((object) != nullptr) {object->Release(); object = nullptr;}

#if defined WINDOWS
#define MULTI_LINE_MACRO_BEGIN do{
#define MULTI_LINE_MACRO_END \
	__pragma(warning(push)) \
	__pragma(warning(disable:4127)) \
    } while (0) \
	__pragma(warning(pop))
#endif

#endif