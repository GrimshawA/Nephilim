#ifndef NephilimUI_MenuBar_h__
#define NephilimUI_MenuBar_h__

#include <Nephilim/UI/Widget.h>

NEPHILIM_NS_BEGIN

/**
	\class UIMenuBar
	\brief A menu bar widget for holding multiple sub menus
*/
class NEPHILIM_API UIMenuBar : public Widget
{
public:
	UIMenuBar();

	void openMenu(const String& name);

	void onAttach(Widget* view);

	void onEvent(Event event, Widget* view);

	void onRender(GraphicsDevice* renderer, Widget* view);

	void addMenu(const String& menuTitle);

	void meteNojo(const String &name);

	Widget* mParent;
};

NEPHILIM_NS_END
#endif // NephilimUI_MenuBar_h__
