#include "SampleKinesis.h"

#include <Nephilim/KinesisWorld.h>

KinesisWorld world;

void SampleKinesis::onCreate()
{	
	world.CreateQuickCircle(200,200,20);
	world.CreateStaticBox(0,600,2500, 10);
}

void SampleKinesis::onEvent(Event &event)
{
   if(event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
   {
	   world.CreateQuickCircle(event.mouseButton.x,event.mouseButton.y,20);
   }
}

void SampleKinesis::onUpdate(Time time)
{ 
	world.update(time.asSeconds());
}

void SampleKinesis::onRender()
{
	getRenderer()->setClearColor(Color::Blue);
	getRenderer()->setProjectionMatrix(View(0,0,1024,768).getMatrix());

	world.drawDebugShapes(getRenderer());
}
