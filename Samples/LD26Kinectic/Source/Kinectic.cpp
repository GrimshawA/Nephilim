#include "Kinectic.h"

#include <Nephilim/KinesisWorld.h>
#include <Nephilim/KinesisDebugDraw.h>
#include <Nephilim/ParticleSystem.h>
#include <Nephilim/Texture.h>
#include <Nephilim/Sprite.h>

KinesisWorld world;

Texture tex;

ParticleSystem p1;


void Kinectic::onCreate()
{	
	world.CreateQuickCircle(200,200,20);
	world.CreateStaticBox(0,600,2500, 10);

	tex.loadFromFile("as.png");

	p1.create();
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

	p1.update(time.asSeconds());
}

void Kinectic::onRender()
{
	getRenderer()->setClearColor(Color::Blue);
	getRenderer()->setProjectionMatrix(View(0,0,1024,768).getMatrix());


	Sprite s;
	s.setTexture(tex);
	s.resize(1024,768);
	getRenderer()->draw(s);

	getRenderer()->draw(KinesisDebugDraw(world));

	getRenderer()->draw(p1);
}
