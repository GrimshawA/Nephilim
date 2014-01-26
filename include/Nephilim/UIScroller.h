#ifndef NephilimUIScroller_h__
#define NephilimUIScroller_h__

#include "Platform.h"
#include "UIViewComponent.h"
#include "Vectors.h"

NEPHILIM_NS_BEGIN

class UIView;

class NEPHILIM_API UIComponentScroll : public UIViewComponent
{
public:
	void onCreate();

	void onEvent(Event event, UIView* view);

	void onUpdate(const Time& time, UIView* view);

	void onRender(Renderer* renderer, UIView* view);

	bool scrolling;
	vec2 lastPosition;
};

NEPHILIM_NS_END

#endif // NephilimUIScroller_h__
