#ifndef SampleScripting_h__
#define SampleScripting_h__

#include <Nephilim/GameCore.h>
#include <Nephilim/Renderer.h>
using namespace pE;

class SampleScripting : public GameCore
{
public:
	void onCreate();
	void onRender();
	void onEvent(Event &event);
	void onUpdate(Time time);
};
#endif // SampleScripting_h__
