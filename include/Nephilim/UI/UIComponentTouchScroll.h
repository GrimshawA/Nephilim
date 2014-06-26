#ifndef NephilimUIComponentTouchScroll_h__
#define NephilimUIComponentTouchScroll_h__

#include <Nephilim/Platform.h>
#include <Nephilim/UIComponent.h>
#include <Nephilim/Color.h>
#include <Nephilim/Vectors.h>

NEPHILIM_NS_BEGIN

class UIView;

class NEPHILIM_API UIComponentScroll : public UIComponent
{
public:
	//UIComponentScroll();

	void onAttach(UIView* view);

	void onEvent(Event event, UIView* view);

	UIView* getSelectedView(UIView* view);
	
	void onUpdate(const Time& time, UIView* view);


	void onRender(Renderer* renderer, UIView* view);

	bool scrolling;
	vec2 lastPosition;

	bool mScrollsHorizontally;
	bool mScrollsVertically;
	bool mPageBased;
};

NEPHILIM_NS_END

#endif // NephilimUIComponentTouchScroll_h__
