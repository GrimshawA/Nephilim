#ifndef SampleSprites_h__
#define SampleSprites_h__

#include <Nephilim/GameCore.h>
#include <Nephilim/Renderer.h>
using namespace nx;

class SampleSprites : public GameCore
{
public:
	void onCreate();
	void onRender();
	void onEvent(Event &event);
	void onUpdate(Time time);
};
#endif // SampleSprites_h__
