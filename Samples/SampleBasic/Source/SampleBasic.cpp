#include "SampleBasic.h"

#include <Nephilim/Image.h>
#include <Nephilim/Texture.h>
#include <Nephilim/Sprite.h>

#include <iostream>
using namespace std;

Vec2f m_pos(200,200);

Image img;

void PortabilityTest::onCreate()
{
	/*if(img.loadFromFile("Buttons.png"))
	{
		cout<<"Image loaded sucessfully."<<endl;
	}

	img.saveToFile("supnigga.png");*/
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
/*
	Texture t;
	t.loadFromImage(img);

	Sprite spr;
	spr.setTexture(t);
	getRenderer()->draw(spr);*/
}
