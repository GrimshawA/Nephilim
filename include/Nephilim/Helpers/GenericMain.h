#ifndef GenericMain_h__
#define GenericMain_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Game/Engine.h>

using namespace NEPHILIM_NS;

// -- This file provides a standard program flow for all platforms

extern void init();
extern void update();
extern void shutdown();

Engine*		   _engine = NULL;

#include "GenericMainAndroid.h"

#ifdef NEPHILIM_DESKTOP

int main(int argc, char** argv)
{
	Engine sdk; _engine = &sdk; sdk.setArgs(argc, argv);

	init();
	while(sdk.isRunning())
	{
		update();
	}
	shutdown();
	_engine = NULL;
	return 0;
}

#endif

#endif // GenericMain_h__
