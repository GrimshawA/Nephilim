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

Engine sdk;

void android_init(){

	static bool alreadyStarted = false;

	if(!alreadyStarted){
		_engine = &sdk;
#if defined NEPHILIM_GLES1
		_engine->glesHint = 1;
#else
		_engine->glesHint = 2;
#endif

		init();

		alreadyStarted = true;
	}
	else{

	}


}

void android_gl_reload()
{
	/*pE::Event ev;
	ev.type = pE::Event::Resume;
	myApp.pendingEvents.push_back(ev);*/
}

void android_render(){
	update();
}

void android_resize(int w, int h){
	_engine = &sdk; // ensure
	_engine->m_surface.m_windowWidth = w;
	_engine->m_surface.m_windowHeight = h;

	/*
	pE::Event ev;
	ev.type = pE::Event::Resized;
	ev.size.width = w;
	ev.size.height = h;
	myApp.pendingEvents.push_back(ev);*/
}

void android_keydown(int key){
//	NEPHILIM_NS::String sd = "Keypressed: " + pE::String::number(key);

	NEPHILIM_NS::Event ev;
	ev.type = NEPHILIM_NS::Event::KeyPressed;

	switch(key){
	case AKEYCODE_A: ev.key.code = NEPHILIM_NS::Keyboard::A;break;
	case AKEYCODE_S: ev.key.code = NEPHILIM_NS::Keyboard::S;break;
	case AKEYCODE_D: ev.key.code = NEPHILIM_NS::Keyboard::D;break;
	case AKEYCODE_W: ev.key.code = NEPHILIM_NS::Keyboard::W;break;
	case AKEYCODE_BACK: ev.key.code = NEPHILIM_NS::Keyboard::AndroidBack;break;
	}

	_engine->injectEvent(ev);
}

void android_touchdown(float x, float y){
	NEPHILIM_NS::Event ev;
	ev.type = NEPHILIM_NS::Event::TouchPressed;
	ev.touch.x = x;
	ev.touch.y = y;
	_engine->injectEvent(ev);
}

void android_touchup(float x, float y){
	NEPHILIM_NS::Event ev;
	ev.type = NEPHILIM_NS::Event::TouchReleased;
	ev.touch.x = x;
	ev.touch.y = y;
	_engine->injectEvent(ev);
}

void android_touchmove(float x, float y){
	NEPHILIM_NS::Event ev;
	ev.type = NEPHILIM_NS::Event::TouchMoved;
	ev.touch.x = x;
	ev.touch.y = y;
	_engine->injectEvent(ev);
}



#endif
#endif // GenericMainAndroid_h__
