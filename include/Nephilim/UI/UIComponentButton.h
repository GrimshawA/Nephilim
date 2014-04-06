#ifndef NephilimUIComponentButton_h__
#define NephilimUIComponentButton_h__

#include <Nephilim/Platform.h>
#include <Nephilim/UIViewComponent.h>

NEPHILIM_NS_BEGIN

class NEPHILIM_API UIComponentButton : public UIViewComponent
{
public:
	UIComponentButton();

	void onAttach(UIView* view);

	void onEvent(Event event, UIView* view);

	void onRender(Renderer* renderer, UIView* view);

	bool hovering;
};

NEPHILIM_NS_END
#endif // NephilimUIComponentButton_h__
