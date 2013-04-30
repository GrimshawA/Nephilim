#include "SampleSprites.h"

#include <Nephilim/View.h>
#include <Nephilim/Texture.h>
#include <Nephilim/Sprite.h>

Texture texture1;

void SampleSprites::onCreate()
{	
	texture1.loadFromFile("as2.png");
}

void SampleSprites::onEvent(Event &event)
{
    
}

void SampleSprites::onUpdate(Time time)
{ 
	
}

void SampleSprites::onRender()
{
	getRenderer()->setClearColor(Color::Blue);
	getRenderer()->setProjectionMatrix(View(0,0,1024,768).getMatrix());

	Sprite demonstration1;
	demonstration1.setTexture(texture1);
	demonstration1.setPosition(400,200);
	demonstration1.setRotation(45);
	demonstration1.setScale(0.5,0.5);
	getRenderer()->draw(demonstration1);
}
