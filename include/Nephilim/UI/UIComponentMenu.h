#ifndef NephilimUIComponentMenu_h__
#define NephilimUIComponentMenu_h__

#include <Nephilim/Platform.h>
#include <Nephilim/UI/UIComponent.h>

NEPHILIM_NS_BEGIN

/*
	\class UIComponentMenuCaster
	\brief Used to open submenus from clicking a view
*/
class NEPHILIM_API UIComponentMenuCaster : public UIComponent
{
public:
	UIComponentMenuCaster();

	void toggleMenu();

	void onAttach(UIView* view);

	void onEvent(Event event, UIView* view);

	void onRender(GraphicsDevice* renderer, UIView* view);
};

NEPHILIM_NS_END
#endif // NephilimUIComponentMenu_h__

