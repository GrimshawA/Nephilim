#ifndef NephilimUIComponentMenuBar_h__
#define NephilimUIComponentMenuBar_h__

#include <Nephilim/Platform.h>
#include <Nephilim/UI/UIComponent.h>
#include <Nephilim/Strings.h>

NEPHILIM_NS_BEGIN

class NEPHILIM_API UIComponentMenuBar : public UIComponent
{
public:
	UIComponentMenuBar();

	void openMenu(const String& name);

	void onAttach(UIView* view);

	void onEvent(Event event, UIView* view);

	void onRender(Renderer* renderer, UIView* view);

	void addMenu(const String& menuTitle);

	void meteNojo(const String &name);

	UIView* mParent;
};

NEPHILIM_NS_END
#endif // NephilimUIComponentMenuBar_h__
