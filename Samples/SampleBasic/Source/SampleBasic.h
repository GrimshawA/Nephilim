#ifndef PortabilityTest_h__
#define PortabilityTest_h__

#include <Nephilim/GameCore.h>
#include <Nephilim/Renderer.h>
#include <Nephilim/Shader.h>
#include <Nephilim/Package.h>
using namespace pE;

class PortabilityTest : public GameCore
{
public:
	void onCreate();
	void onRender();
	void onEvent(Event &event);
	void onUpdate(Time time);

	Shader s;
};

#endif // PortabilityTest_h__
