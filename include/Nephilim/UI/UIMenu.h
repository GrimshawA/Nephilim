#ifndef NephilimUI_Menu_h__
#define NephilimUI_Menu_h__

#include <Nephilim/UI/UIView.h>

NEPHILIM_NS_BEGIN

/*
	\class UIMenu
	\brief For using in menu bars, displays a list of items
*/
class NEPHILIM_API UIMenu : public UIView
{
public:
	UIMenu();

	void toggleMenu();

	void onAttach(UIView* view);

	void onEvent(Event event, UIView* view);

	void onRender(GraphicsDevice* renderer, UIView* view);
};

NEPHILIM_NS_END
#endif // NephilimUI_Menu_h__

