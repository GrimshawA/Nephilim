#ifndef NephilimRazer_h__
#define NephilimRazer_h__

#include <Nephilim/Clock.h>
#include <Nephilim/Event.h>
#include <Nephilim/Renderer.h>
#include <Nephilim/Surface.h>
#include <Nephilim/Logger.h>
#include <Nephilim/View.h>
#include <Nephilim/File.h>
#include <Nephilim/DataStream.h>
#include <Nephilim/Camera.h>
#include <Nephilim/FileSystem.h>
#include <Nephilim/FileDialog.h>
#include <Nephilim/UIWindow.h>
#include <Nephilim/UIButton.h>
#include <Nephilim/InputGrabber.h>
#include <Nephilim/Geometry.h>
using namespace nx;

#include <vector>

class Razer
{
public:
	void onCreate();
	void onRender(Renderer* renderer);
	void onEvent(Event &event);
	void onUpdate(Time time);

	void onLoadModel();
	void onLoadTexture();
	void onSaveScene();
	void onLoadScene();

	UIWindow m_interface;
	InputGrabber input;
};

#endif // NephilimRazer_h__