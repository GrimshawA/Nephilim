#define ANDROID_PACKAGE_NAME com_nephilim_sampleui
#define ANDROID_ACTIVITY_NAME SampleUI
#include <Nephilim/GenericMain.h>
#include "SampleUI.h"

SampleUI sample;

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

