#ifndef PARABOLA_APPLICATION_H
#define PARABOLA_APPLICATION_H

#include "Platform.h"
#include "Strings.h"
#include "Engine.h"
#include "Application.h"
#include "Event.h"
#include <stdio.h>

pE::Engine* gEngine = NULL;
pE::Application myApp;

extern void applicationStartup(pE::Engine** engine);
extern void applicationUpdate();
extern void applicationCleanup();

#ifdef PARABOLA_ANDROID

#if !defined ANDROID_PACKAGE_NAME || !defined ANDROID_ACTIVITY_NAME
#error Cannot build for Android platform without specifying the ANDROID_PACKAGE_NAME and ANDROID_ACTIVITY_CLASS
#endif

#include "AndroidJNI.h"
#include <android/keycodes.h>

void android_init(){
	// first register in the application the interface
	//pE::Application::myInstance->jniEnv = jEnv;
	static bool alreadyStarted = false;

	if(!alreadyStarted){ 
		applicationStartup(&gEngine);
		alreadyStarted = true;
	}
	else{
		
	}
}

void android_gl_reload()
{
	pE::Event ev;
	ev.type = pE::Event::Resume;
	myApp.pendingEvents.push_back(ev);
}

void android_render(){
	applicationUpdate();
}

void android_resize(int w, int h){ 
	myApp.myWindowWidth = w; 
	myApp.myWindowHeight = h;

	pE::Event ev;
	ev.type = pE::Event::Resized; 
	ev.size.width = w;
	ev.size.height = h;
	myApp.pendingEvents.push_back(ev);
}

void android_keydown(int key){
	pE::String sd = "Keypressed: " + pE::String::number(key);

	pE::Event ev;
	ev.type = pE::Event::KeyPressed;

	switch(key){ 
		case AKEYCODE_A: ev.key.code = pE::Keyboard::A;break;
		case AKEYCODE_S: ev.key.code = pE::Keyboard::S;break;
		case AKEYCODE_D: ev.key.code = pE::Keyboard::D;break;
		case AKEYCODE_W: ev.key.code = pE::Keyboard::W;break;
		case AKEYCODE_BACK: ev.key.code = pE::Keyboard::AndroidBack;break;
	}

	
	myApp.pendingEvents.push_back(ev);
}

void android_touchdown(float x, float y){
	pE::Event ev;
	ev.type = pE::Event::TouchPressed;
	ev.x = x;
	ev.y = y;
	myApp.pendingEvents.push_back(ev); 
}

void android_touchup(float x, float y){
	pE::Event ev;
	ev.type = pE::Event::TouchReleased;
	ev.x = x;
	ev.y = y;
	myApp.pendingEvents.push_back(ev); 
}

void android_touchmove(float x, float y){
	pE::Event ev;
	ev.type = pE::Event::TouchMoved;
	ev.x = x;
	ev.y = y;
	myApp.pendingEvents.push_back(ev); 
}

#elif defined PARABOLA_WINDOWS

	int main(int argc, char** argv){
		applicationStartup(&gEngine);

		while(myApp.running()){
			applicationUpdate();
		}
		applicationCleanup();
		return 0;
	}
#elif defined PARABOLA_IPHONE
void ios_bridge_initialize()
{
	applicationStartup(&gEngine);
}

void ios_bridge_update()
{
	applicationUpdate();
}

void ios_bridge_touch_pressed(int x, int y, int id)
{
	if(gEngine)
	{
		pE::Event ev;
		ev.type = pE::Event::TouchPressed;
		ev.x = x;
		ev.y = y;
		gEngine->inject(ev);
	}
}
#endif

#endif