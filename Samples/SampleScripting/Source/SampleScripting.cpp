#include "SampleScripting.h"
#include <Nephilim/Renderer.h>
#include <Nephilim/View.h>

#include <iostream>
using namespace std;

//#include <Nephilim/ASXEngine.h>

//ASXEngine engine;

void SampleScripting::onCreate()
{
	//ASXModuleBuilder builder(engine, "core");
	//builder.addSource(sampleScript);
	//builder.build();
}

void SampleScripting::onEvent(Event &event)
{
    
}


void SampleScripting::onUpdate(Time time)
{ 
	
}

void SampleScripting::onRender()
{
	// Redundant, this is already activated implicitly
	getRenderer()->setDefaultTarget();
	getRenderer()->setDefaultShader();
	getRenderer()->setDefaultBlending();
	getRenderer()->setDefaultTransforms();
	getRenderer()->setDefaultViewport();
	getRenderer()->setDefaultDepthTesting();
	
	getRenderer()->setProjectionMatrix(View(0,0,1000,768).getMatrix());
	getRenderer()->drawDebugCircle(Vec2f(500,250), 40, Vec2f(), Color::Green);
}
