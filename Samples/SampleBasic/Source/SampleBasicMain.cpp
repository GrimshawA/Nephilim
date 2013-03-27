#define ANDROID_PACKAGE_NAME com_parabolaengine_scriptedgamecore
#define ANDROID_ACTIVITY_NAME ScriptedGameCore
#include <Nephilim/ParabolaMain.h>
#include <Nephilim/Engine.h>
#include "SampleBasic.h"
using namespace pE;

Engine sdk;
PortabilityTest test;

void applicationStartup(pE::Engine** engine)
{
	sdk.init();
	sdk.execute(&test);
	*engine = &sdk;
}

void applicationUpdate()
{
	sdk.update();
}

void applicationCleanup()
{
	
}