#include <Nephilim/UI/UITreeView.h>
#include <Nephilim/UI/UIComponentTreeView.h>

NEPHILIM_NS_BEGIN

/// Construct the tree view
UITreeView::UITreeView()
: UIView()
{
	addComponent(new UIComponentTreeView);
}

NEPHILIM_NS_END