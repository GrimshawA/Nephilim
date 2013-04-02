#ifndef GenericMainIOS_h__
#define GenericMainIOS_h__

#include "Platform.h"

// -- Assumes a _engine global variable declared previously to communicate with

#if defined NEPHILIM_IOS

void ios_bridge_initialize()
{
	applicationStartup(&gEngine);
}

void ios_bridge_update()
{
	applicationUpdate();
}

void ios_bridge_touch_pressed(int x, int y, int id)
{
	if(gEngine)
	{
		pE::Event ev;
		ev.type = pE::Event::TouchPressed;
		ev.x = x;
		ev.y = y;
		gEngine->inject(ev);
	}
}

#endif
#endif // GenericMainIOS_h__
