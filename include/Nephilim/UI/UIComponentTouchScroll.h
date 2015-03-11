#ifndef NephilimUIComponentTouchScroll_h__
#define NephilimUIComponentTouchScroll_h__

#include <Nephilim/Platform.h>
#include <Nephilim/UI/UIController.h>
#include <Nephilim/Foundation/Color.h>
#include <Nephilim/Foundation/Vector.h>

NEPHILIM_NS_BEGIN

class Widget;

class NEPHILIM_API UIComponentScroll : public UIController
{
public:
	//UIComponentScroll();

	void onAttach(Widget* view);

	void onEvent(Event event, Widget* view);

	Widget* getSelectedView(Widget* view);
	
	void onUpdate(const Time& time, Widget* view);


	void onRender(GraphicsDevice* renderer, Widget* view);

	bool scrolling;
	vec2 lastPosition;

	bool mScrollsHorizontally;
	bool mScrollsVertically;
	bool mPageBased;
};

NEPHILIM_NS_END

#endif // NephilimUIComponentTouchScroll_h__
