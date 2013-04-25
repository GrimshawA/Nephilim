#define ANDROID_PACKAGE_NAME com_nephilim_samplefs
#define ANDROID_ACTIVITY_NAME SampleFS
#include <Nephilim/GenericMain.h>
#include "SampleFS.h"

SampleFS sample;

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

