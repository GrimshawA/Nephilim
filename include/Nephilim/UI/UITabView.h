#ifndef NephilimUI_TabView_h__
#define NephilimUI_TabView_h__

#include <Nephilim/UI/Widget.h>

#include <vector>

NEPHILIM_NS_BEGIN

/**
	\class UITabView
	\brief A panel with multiple switchable sub panels
*/
class NEPHILIM_API UIComponentTabView : public Widget
{
public:
	UIComponentTabView();

	/// Show another tab by its index
	void onTabButtonClicked(std::size_t index);

	void onEvent(Event event, Widget* view);

	void onRender(GraphicsDevice* renderer, Widget* view);

	void refreshTabButtons();

	/// Tabs in order
	std::vector<Widget*> tabs;
	Widget* parent;
};

NEPHILIM_NS_END
#endif // NephilimUI_TabView_h__
