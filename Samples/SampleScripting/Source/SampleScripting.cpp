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
	getRenderer()->setDefaultTarget();
	getRenderer()->setDefaultShader();
	getRenderer()->setDefaultBlending();
	getRenderer()->setDefaultTransforms();
	getRenderer()->setDefaultViewport();
	
	getRenderer()->setProjectionMatrix(View(0,0,1000,1000).getMatrix());
	getRenderer()->drawDebugCircle(Vec2f(30,30), 40, Vec2f(), Color::Orange);
}
