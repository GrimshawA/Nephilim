#ifndef SampleKinesis_h__
#define SampleKinesis_h__

#include <Nephilim/GameCore.h>
#include <Nephilim/Renderer.h>
using namespace nx;

class Kinectic : public GameCore
{
public:
	void onCreate();
	void onRender();
	void onEvent(Event &event);
	void onUpdate(Time time);
};

#endif // SampleKinesis_h__
