#ifndef SampleUI_h__
#define SampleUI_h__

#include <Nephilim/GameCore.h>
#include <Nephilim/Renderer.h>
#include <Nephilim/StateStack.h>
#include <Nephilim/State.h>
using namespace nx;

// Samples
#include "SampleTransition.h"

class SampleBox : public GameCore
{
public:
	void onCreate();
	void onRender();
	void onEvent(Event &event);
	void onUpdate(Time time);

	StateStack m_stack;

	// Samples
	SampleTransition* m_transition;
};
#endif // SampleUI_h__
