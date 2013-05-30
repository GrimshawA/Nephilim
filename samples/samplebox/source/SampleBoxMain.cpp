#define ANDROID_PACKAGE_NAME com_nephilim_samplebox
#define ANDROID_ACTIVITY_NAME SampleBox
#include <Nephilim/GenericMain.h>
#include "SampleBox.h"

SampleBox sample;

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

