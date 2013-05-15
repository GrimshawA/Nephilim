#define ANDROID_PACKAGE_NAME com_nephilim_ts
#define ANDROID_ACTIVITY_NAME TriangleSuper
#include <Nephilim/GenericMain.h>
#include "SampleSprites.h"

SampleSprites sample;

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

