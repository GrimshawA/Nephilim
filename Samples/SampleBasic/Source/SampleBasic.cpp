#include "SampleBasic.h"
#include <Nephilim/CGL.h>
#include <Nephilim/Image.h>
#include <Nephilim/Texture.h>
#include <Nephilim/Sprite.h>

//#define PROFILER_DISABLE // completely removes all overhead of profiling
#define PROFILER_DEBUG_ONLY
#include <Nephilim/Profiler.h>
#include <Nephilim/Engine.h>


#include <iostream>
using namespace std;

Vec2f m_pos(200,200);

Image img;

Texture t;
void PortabilityTest::onCreate()
{

	img.loadFromFile("K:/scary_tree.png");
	t.loadFromImage(img);

/*	cout << "Engine information" << endl;
	cout << "Version: " << Engine::getVersionString() << endl;
	cout << "OpenGL: " << getGLVersionString() << endl;
	cout << "OpenGL Vendor: " << getGLVendorString() << endl;
	cout << "OpenGL Renderer: " << getGLRendererString() << endl;
	cout<< "Shader information" << endl;
	cout << Shader::getVersion() << endl;
	cout << Shader::getCurrentActiveProgram() << endl;
	cout << endl;

	ShaderGen::prepareDefault(defaultShader);
	*/
	PRINTLOG("Renderer", "Renderer: %s\n", getRenderer()->getName().c_str());
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
	View v;
	v.setRect(0,0,10,10);

	Sprite s;
	s.setTexture(t);
	s.setColor(Color(255,0,255,255));
	getRenderer()->draw(s);
}
