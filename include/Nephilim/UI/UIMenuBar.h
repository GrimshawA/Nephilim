#ifndef NephilimUI_MenuBar_h__
#define NephilimUI_MenuBar_h__

#include <Nephilim/UI/UIView.h>

NEPHILIM_NS_BEGIN

/**
	\class UIMenuBar
	\brief A menu bar widget for holding multiple sub menus
*/
class NEPHILIM_API UIMenuBar : public UIView
{
public:
	UIMenuBar();

	void openMenu(const String& name);

	void onAttach(UIView* view);

	void onEvent(Event event, UIView* view);

	void onRender(GraphicsDevice* renderer, UIView* view);

	void addMenu(const String& menuTitle);

	void meteNojo(const String &name);

	UIView* mParent;
};

NEPHILIM_NS_END
#endif // NephilimUI_MenuBar_h__
