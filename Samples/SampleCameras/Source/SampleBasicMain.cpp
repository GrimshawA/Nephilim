#define ANDROID_PACKAGE_NAME com_nephilim_samplebasic
#define ANDROID_ACTIVITY_NAME SampleBasic
#include <Nephilim/GenericMain.h>
#include "SampleBasic.h"
//#include <Nephilim/ScriptedGameCore.h>

SampleUI test;
//ScriptedGameCore a;

void init()
{    
	_engine->init();
	_engine->execute(&test);


}

void update()
{
	_engine->update();
}

void shutdown()
{
	_engine->shutdown();
}

