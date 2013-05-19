#ifndef RazerApp_h__
#define RazerApp_h__

#include <Nephilim/GameCore.h>
#include <Nephilim/Renderer.h>
using namespace nx;

#include "Razer.h"

/**
	\class RazerApp
	\brief The basic skeleton holding the Razer 3D Editor
*/	
class RazerApp : public GameCore
{
public:
	void onCreate();
	void onRender();
	void onEvent(Event &event);
	void onUpdate(Time time);

	Razer* razer;
};
#endif // RazerApp_h__

