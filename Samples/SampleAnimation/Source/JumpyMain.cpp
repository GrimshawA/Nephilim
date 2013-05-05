#define ANDROID_PACKAGE_NAME com_nephilim_jumpy
#define ANDROID_ACTIVITY_NAME Jumpy
#include <Nephilim/GenericMain.h>
#include "Jumpy.h"

Jumpy jumpy;

void init()
{    
	_engine->init();
	_engine->execute(&jumpy);
}

void update()
{
	_engine->update();
}

void shutdown()
{
	_engine->shutdown();
}

