#define ANDROID_PACKAGE_NAME com_nephilim_samplebasic
#define ANDROID_ACTIVITY_NAME SampleBasic
#include <Nephilim/GenericMain.h>
#include "RazerApp.h"

RazerApp app;

void init()
{    
	_engine->init();
	_engine->execute(&app);
}

void update()
{
	_engine->update();
}

void shutdown()
{
	_engine->shutdown();
}

