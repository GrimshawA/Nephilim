#ifndef NephilimUIComponentTreeView_h__
#define NephilimUIComponentTreeView_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Signals.h>
#include <Nephilim/UI/UIComponent.h>

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

	/// Computes the total height of the child item, including all its nested subtrees
	vec2 computeChildSize(int index);

	/// Get current size of this subtree container
	/// This returns the size the container should be according to its items, not what is currently IS
	vec2 getSize();

	/// Get the current size of the <index> child item
	vec2 getItemSize(int index);

	/// Check if any of the children items are expandible (subtrees)
	bool isSubTree(int index);

	/// Whenever a child is added to any of this UIView's children
	/// we need to act upon it
	void onChildAddedToChild(UIView* subChild, UIView* child);

	/// Expands/Collapses the child item if it exists
	void toggleItem(UIView* item);

	/// Recomputes all sizes and positions for the entire hierarchy (can be heavy)
	/// Resizes the treeView container view to fit its children unless its at level 0
	void recomputeTree();

	/// Toggle will expand/collapse the tree view
	void toggle();

	void onRender(Renderer* renderer, UIView* view);

	float mLineHeight;

	bool mSubTreeView;
	int mSubTreeLevel;

	float mSpacing; ///< Amount of space left empty between entries

	bool collapsed; ///< A tree view can be either collapsed or expanded to show its children items
};

class NEPHILIM_API UIComponentTreeViewItem : public UIComponent
{
public:
	void toggle();

	void onRender(Renderer* renderer, UIView* view);
};

NEPHILIM_NS_END
#endif // NephilimUIComponentTreeView_h__
