#include <Nephilim/UI/UITreeView.h>
#include <Nephilim/UI/UIComponentTreeView.h>

NEPHILIM_NS_BEGIN

/// Construct the tree view
UITreeView::UITreeView()
: UIView()
{
	treeViewComponent = new UIComponentTreeView;
	addComponent(treeViewComponent);
}

NEPHILIM_NS_END