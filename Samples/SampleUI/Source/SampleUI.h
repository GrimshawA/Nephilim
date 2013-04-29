#ifndef SampleUI_h__
#define SampleUI_h__

#include <Nephilim/GameCore.h>
#include <Nephilim/Renderer.h>
#include <Nephilim/Shader.h>
#include <Nephilim/ShaderGen.h>
#include <Nephilim/Package.h>
#include <Nephilim/Framebuffer.h>
#include <Nephilim/UIWindow.h>
using namespace nx;

class SampleUI : public GameCore
{
public:
	void onCreate();
	void onRender();
	void onEvent(Event &event);
	void onUpdate(Time time);

	UIWindow ui;
};
#endif // SampleUI_h__
