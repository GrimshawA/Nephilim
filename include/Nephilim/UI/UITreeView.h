#ifndef UITreeView_h__
#define UITreeView_h__

#include <Nephilim/Platform.h>
#include <Nephilim/UI/UIView.h>
#include <Nephilim/Graphics/Text.h>

NEPHILIM_NS_BEGIN

class UIComponentTreeView;

class NEPHILIM_API UITreeView : public UIView
{
public:

	/// The component that manages the tree view
	UIComponentTreeView* treeViewComponent = nullptr;

public:

	/// Construct the tree view
	UITreeView();
};

NEPHILIM_NS_END
#endif // UITreeView_h__
