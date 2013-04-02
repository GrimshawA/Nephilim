#ifndef GenericMainAndroid_h__
#define GenericMainAndroid_h__

#include "Platform.h"

// -- Assumes a _engine global variable declared previously to communicate with

#if defined NEPHILIM_ANDROID

#include <Nephilim/AndroidInterface.h>

#if !defined ANDROID_PACKAGE_NAME || !defined ANDROID_ACTIVITY_NAME
#error Cannot build for Android platform without specifying the ANDROID_PACKAGE_NAME and ANDROID_ACTIVITY_CLASS
#endif

#include "AndroidJNI.h"
#include <android/keycodes.h>

void android_init(){
	// first register in the application the interface
	//pE::Application::myInstance->jniEnv = jEnv;
	/*static bool alreadyStarted = false;

	if(!alreadyStarted){
		applicationStartup(&gEngine);
		alreadyStarted = true;
	}
	else{

	}*/
}

void android_gl_reload()
{
	/*pE::Event ev;
	ev.type = pE::Event::Resume;
	myApp.pendingEvents.push_back(ev);*/
}

void android_render(){
	//applicationUpdate();
}

void android_resize(int w, int h){
	/*myApp.myWindowWidth = w;
	myApp.myWindowHeight = h;

	pE::Event ev;
	ev.type = pE::Event::Resized;
	ev.size.width = w;
	ev.size.height = h;
	myApp.pendingEvents.push_back(ev);*/
}

void android_keydown(int key){
	/*pE::String sd = "Keypressed: " + pE::String::number(key);

	pE::Event ev;
	ev.type = pE::Event::KeyPressed;

	switch(key){
	case AKEYCODE_A: ev.key.code = pE::Keyboard::A;break;
	case AKEYCODE_S: ev.key.code = pE::Keyboard::S;break;
	case AKEYCODE_D: ev.key.code = pE::Keyboard::D;break;
	case AKEYCODE_W: ev.key.code = pE::Keyboard::W;break;
	case AKEYCODE_BACK: ev.key.code = pE::Keyboard::AndroidBack;break;
	}


	myApp.pendingEvents.push_back(ev);*/
}

void android_touchdown(float x, float y){
	/*pE::Event ev;
	ev.type = pE::Event::TouchPressed;
	ev.x = x;
	ev.y = y;
	myApp.pendingEvents.push_back(ev);*/
}

void android_touchup(float x, float y){
	/*pE::Event ev;
	ev.type = pE::Event::TouchReleased;
	ev.x = x;
	ev.y = y;
	myApp.pendingEvents.push_back(ev);*/
}

void android_touchmove(float x, float y){
	/*pE::Event ev;
	ev.type = pE::Event::TouchMoved;
	ev.x = x;
	ev.y = y;
	myApp.pendingEvents.push_back(ev);*/
}



#endif
#endif // GenericMainAndroid_h__
