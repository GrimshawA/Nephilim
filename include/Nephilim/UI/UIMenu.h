#ifndef NephilimUI_Menu_h__
#define NephilimUI_Menu_h__

#include <Nephilim/UI/Widget.h>

NEPHILIM_NS_BEGIN

/*
	\class UIMenu
	\brief For using in menu bars, displays a list of items
*/
class NEPHILIM_API UIMenu : public Widget
{
public:
	UIMenu();

	void toggleMenu();

	void onAttach(Widget* view);

	void onEvent(Event event, Widget* view);

	void onRender(GraphicsDevice* renderer, Widget* view);
};

NEPHILIM_NS_END
#endif // NephilimUI_Menu_h__

