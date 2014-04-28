#ifndef NephilimUIComponentTabView_h__
#define NephilimUIComponentTabView_h__

#include <Nephilim/Platform.h>
#include <Nephilim/UIComponent.h>

#include <vector>

NEPHILIM_NS_BEGIN

class UIView;

class NEPHILIM_API UIComponentTabView : public UIViewComponent
{
public:
	UIComponentTabView();

	void onAttach(UIView* view);

	/// Show another tab by its index
	void onTabButtonClicked(size_t index);

	void onEvent(Event event, UIView* view);

	void onRender(Renderer* renderer, UIView* view);

	void refreshTabButtons();

	/// Tabs in order
	std::vector<UIView*> tabs;
	UIView* parent;
};

NEPHILIM_NS_END
#endif // NephilimUIComponentTabView_h__
