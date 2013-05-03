#include "SampleUI.h"
#include <Nephilim/CGL.h>
#include <Nephilim/Image.h>
#include <Nephilim/Texture.h>
#include <Nephilim/Sprite.h>
#include <Nephilim/MMath.h>
#include <Nephilim/Matrix.h>
#include <Nephilim/Geometry.h>
#include <Nephilim/Profiler.h>
#include <Nephilim/Text.h>
#include <Nephilim/Engine.h>
//#include <Nephilim/ASXEngine.h>
#include <Nephilim/File.h>

#include <iostream>
using namespace std;

Text text;
Font *font;

void SampleUI::onCreate()
{	

	font = new Font();
	if(font->loadFromFile("arial.ttf"))
	{
		Log("Arial loaded from file.");
	}

	text.setFont(*font);
	text.setString("Hello world\nWe are backkkkkkkkkkkkkkkkkkkkkkkkk!\nThis is great I believe!! :)");
	text.setColor(Color::Orange);

	Image readyFont = font->getTexture(text.getCharacterSize()).copyToImage();
	readyFont.saveToFile("readyFont.png"); 
	//Log("Saving to disk texture page %d", font->getTexture(text.getCharacterSize()).m_texture);
	
	
	
	/*
	// create ui
	UIControl* control1 = new UIControl(), *control2 = new UIControl(), *control3 = new UIControl();
	control1->setRect(FloatRect(0,0,500,1000));
	control1->setProperty<Color>("background-color", Color::Orange);
	control2->setRect(FloatRect(500,0,500,1000));
	control2->setProperty<Color>("background-color", Color::Blue);
	control3->setRect(FloatRect(50,0,200,200));
	control3->setProperty<Color>("background-color", Color::Green);
	ui["central"]->addControl(control1);
	ui["central"]->addControl(control2);
	control1->addControl(control3);


	File a("a.txt");
	if(a)
	{
		cout << "Text: "<<a.getLine()<<endl;
	}
	*/
	/*ASXEngine scripts;

	ASXModuleBuilder scriptbuilder(scripts, "myModule");
	scriptbuilder.addSourceFile("script.fuse");
	scriptbuilder.addBytecodeFile("compiled_script.fuse");
	scriptbuilder.addSource("float twice(float num, int num2, float num3){return num+num2+num3;}");
	ASXModule script = scriptbuilder.build();

	ASXModuleWriter writer(script);
	writer.save("bytes.fuse");

	ASXRuntime context(scripts);

	ASXFunction<float, float, int, float> tst(script, context, "float twice(float,int,float)");
	printf("Script returned: %f\n", tst(20.f, 20*5, 5.f));*/

	//context.reset(script);
}

void SampleUI::onEvent(Event &event)
{
    
}


void SampleUI::onUpdate(Time time)
{ 
	
}



void SampleUI::onRender()
{
	// Ensure default shader
	getRenderer()->setDefaultShader();
	getRenderer()->setClearColor(Color::Black);	
	getRenderer()->setProjectionMatrix(mat4(View(0,0,1000,1000).getTransform().getMatrix()));
	getRenderer()->setViewMatrix(mat4());
	getRenderer()->setModelMatrix(mat4());

	// Draw to arbitrary frame buffer
	// UI only uses VertexArray geometry --automatically works
	//ui.draw(getRenderer());

	getRenderer()->setDefaultTexture();
	getRenderer()->setDefaultBlending();
	
	getRenderer()->draw(text);
}
