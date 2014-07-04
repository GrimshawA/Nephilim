#ifndef NephilimUIComponentTreeView_h__
#define NephilimUIComponentTreeView_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Signals.h>
#include <Nephilim/UIComponent.h>

NEPHILIM_NS_BEGIN

/**
	\class UIComponentTreeView
	\brief Tree view explorer widget

	Specification:
	1. The UIView which has the component UIComponentTreeView can have N children
	2. Each of those children is either not expandable if there are no proper subgroups as its children
	3. Or it is expandable if there is a child in it that contains a subgroup
	4. Containing a subgroup means that the container UIView also has a UIComponentTreeView bound in it
*/
class NEPHILIM_API UIComponentTreeView : public UIComponent
{
public:
	UIComponentTreeView();

	/// Called on the component when the UIView it is attached to has a new child
	virtual void onChildAttached(UIView* child);

	void updateItemPositions();

	/// Whenever a child is added to any of this UIView's children
	/// we need to act upon it
	void onChildAddedToChild(UIView* subChild, UIView* child);

	/// Grows one of the local items by an amount
	void growItem(UIView* childItem, float amount);

	void onRender(Renderer* renderer, UIView* view);

	bool mSubTreeView;
	int mSubTreeLevel;

	sigc::signal<void, UIView*, float> onChildItemGrow;
};

class NEPHILIM_API UIComponentTreeViewItem : public UIComponent
{
public:
	void onRender(Renderer* renderer, UIView* view);
};

NEPHILIM_NS_END
#endif // NephilimUIComponentTreeView_h__
