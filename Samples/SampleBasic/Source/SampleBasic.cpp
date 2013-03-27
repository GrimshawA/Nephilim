#include "SampleBasic.h"

#include <iostream>
using namespace std;
	
void PortabilityTest::onCreate()
{
	
}

void PortabilityTest::onEvent(Event &event)
{
	
}

void PortabilityTest::onUpdate(Time time)
{
	
}

void PortabilityTest::onRender()
{
	getRenderer()->drawDebugCircle(Vec2f(200,200), 30, Vec2f(), Color::Red);
}
