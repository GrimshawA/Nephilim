#ifndef NephilimUIComponentMenu_h__
#define NephilimUIComponentMenu_h__

#include <Nephilim/Platform.h>
#include <Nephilim/UI/UIComponent.h>

NEPHILIM_NS_BEGIN

class NEPHILIM_API UIComponentMenu : public UIComponent
{
public:
	UIComponentMenu();

	void onAttach(UIView* view);

	void onEvent(Event event, UIView* view);

	void onRender(Renderer* renderer, UIView* view);
};

NEPHILIM_NS_END
#endif // NephilimUIComponentMenu_h__

