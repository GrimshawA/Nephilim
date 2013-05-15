#define ANDROID_PACKAGE_NAME com_nephilim_samplescripting
#define ANDROID_ACTIVITY_NAME SampleScripting
#include <Nephilim/GenericMain.h>
#include "SampleScripting.h"

SampleScripting sample;

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

