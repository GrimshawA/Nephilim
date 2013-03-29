#include "SampleBasic.h"

#include <iostream>
using namespace std;

Vec2f m_pos(200,200);

void PortabilityTest::onCreate()
{

}

void PortabilityTest::onEvent(Event &event)
{
        if(event.type == Event::MouseButtonPressed)
        {
            m_pos.x = event.mouseButton.x;
        }
}

void PortabilityTest::onUpdate(Time time)
{

}

void PortabilityTest::onRender()
{
	getRenderer()->drawDebugCircle(Vec2f(m_pos.x,200), 30, Vec2f(), Color::Red);
}
