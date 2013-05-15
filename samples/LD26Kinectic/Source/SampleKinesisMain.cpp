#define ANDROID_PACKAGE_NAME com_nephilim_kinectic
#define ANDROID_ACTIVITY_NAME Kinectic
#include <Nephilim/GenericMain.h>
#include "Kinectic.h"

Kinectic sample;

void init()
{    
	_engine->init();
	_engine->execute(&sample);
}

void update()
{
	_engine->update();
}

void shutdown()
{
	_engine->shutdown();
}

