#include "SampleKinesis.h"

#include <Nephilim/KinesisWorld.h>

KxScene world;

void Kinectic::onCreate()
{	
	world.CreateQuickCircle(200,200,20);
	world.CreateStaticBox(0,600,2500, 10);
}

void Kinectic::onEvent(Event &event)
{
   if(event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
   {
	   world.CreateQuickCircle(event.mouseButton.x,event.mouseButton.y,20);
   }
}

void Kinectic::onUpdate(Time time)
{ 
	world.update(time.asSeconds());
}

void Kinectic::onRender()
{
	getRenderer()->setClearColor(Color::Blue);
	getRenderer()->setProjectionMatrix(View(0,0,1024,768).getMatrix());

	world.drawDebugShapes(getRenderer());
}
