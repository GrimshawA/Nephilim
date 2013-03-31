#include "SampleBasic.h"
#include <Nephilim/CGL.h>
#include <Nephilim/Image.h>
#include <Nephilim/Texture.h>
#include <Nephilim/Sprite.h>


#include <iostream>
using namespace std;

Vec2f m_pos(200,200);

Image img;

static const char gVertexShader2[] =
	"#version 330\n"

	"in vec4 vPosition;\n"
	"in vec4 ccc;"
	"uniform mat4 projectionMatrix;"
	"uniform mat4 modelViewMatrix;"
	"out vec4 fcolor;"
	"void main() {\n"
	"  gl_Position = projectionMatrix * modelViewMatrix * vPosition;\n"
	"  fcolor = ccc;"
	"}\n";

static const char gFragmentShader2[] = 
	"#version 330\n"
	"in vec4 fcolor;"
	"out vec4 output;"
	"void main() {\n"
	"  output = fcolor;\n"
	"}\n";

void PortabilityTest::onCreate()
{
	cout<< "Shader information" << endl;
	cout << Shader::getVersion() << endl;
	cout << Shader::getCurrentActiveProgram() << endl;
	cout << endl;


	if(s.loadShader(Shader::VertexUnit, gVertexShader2))
	{
		cout << "Loaded vertex shader!" << endl;
	}
	if(s.loadShader(Shader::FragmentUnit, gFragmentShader2))
	{
		cout << "Loaded fragment shader!" << endl;
	}
	if(s.create())
	{
		cout << "Shader program is done." << endl;
	}

	
	PackageBuilder package;
	package.addFile("beauty.jpg", "beauty.jpg");
	if(package.build())
	{
		cout << "Package built." << endl;
	}
	else
	{
		cout << "Package failed to create" << endl;
	}

	Package extractor("package.pkg");
	extractor.extract("extracted_package");
}

void PortabilityTest::onEvent(Event &event)
{
        if(event.type == Event::MouseButtonPressed)
        {
            m_pos.x = event.mouseButton.x;
        }
}

float elapsed = 0.f;

void PortabilityTest::onUpdate(Time time)
{
	elapsed += time.asSeconds();
	//printf("Elapsed: %f\n", elapsed);
}

void PortabilityTest::onRender()
{
	getRenderer()->drawDebugCircle(Vec2f(m_pos.x,200), 30, Vec2f(), Color::Red);
	
	Texture t;
	t.loadFromImage(img);

	Sprite spr;
	spr.setTexture(t);
	getRenderer()->draw(spr);
	
	//s.bind();
}
