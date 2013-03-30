#define ANDROID_PACKAGE_NAME com_parabolaengine_scriptedgamecore
#define ANDROID_ACTIVITY_NAME ScriptedGameCore
#include <Nephilim/ParabolaMain.h>
#include <Nephilim/Engine.h>
#include "SampleBasic.h"
using namespace pE;

#include <Nephilim/ScriptedGameCore.h>

Engine sdk;
PortabilityTest test;
ScriptedGameCore a;

void applicationStartup(pE::Engine** engine)
{
	sdk.init();
	sdk.execute(&a);
	*engine = &sdk;
    printf("App::Start\n");
}

void applicationUpdate()
{

	sdk.update();
}

void applicationCleanup()
{

}
