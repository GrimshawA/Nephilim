#include "RazerApp.h"

void RazerApp::onCreate()
{
	razer = new Razer();
	razer->onCreate();
}

void RazerApp::onEvent(Event &event)
{
	razer->onEvent(event);
}

void RazerApp::onUpdate(Time time)
{
	razer->onUpdate(time);
}

void RazerApp::onRender()
{
	razer->onRender(getRenderer());
}
