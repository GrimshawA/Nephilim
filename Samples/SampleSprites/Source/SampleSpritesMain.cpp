#define ANDROID_PACKAGE_NAME com_nephilim_samplesprites
#define ANDROID_ACTIVITY_NAME SampleSprites
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

