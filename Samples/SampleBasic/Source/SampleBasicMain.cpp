#define ANDROID_PACKAGE_NAME com_parabolaengine_scriptedgamecore
#define ANDROID_ACTIVITY_NAME ScriptedGameCore
#include <Nephilim/GenericMain.h>
#include "SampleBasic.h"
//#include <Nephilim/ScriptedGameCore.h>

PortabilityTest test;
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

