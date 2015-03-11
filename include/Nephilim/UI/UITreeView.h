#ifndef UITreeView_h__
#define UITreeView_h__

#include <Nephilim/UI/Widget.h>

NEPHILIM_NS_BEGIN

class DataModel;
class UITreeNode;
class UITreeViewItem;

/**
	\class UITreeView
	\brief Official widget for displaying tree views
*/
class NEPHILIM_API UITreeView : public Widget
{
public:

	/// The tree view is composed by N root items, which can have their own subitems
	std::vector<UITreeViewItem*> items;

	/// The model for this tree view
	DataModel* _dataModel = nullptr;


	std::vector<Widget*> selectedItems;


	float mLineHeight;

	bool mSubTreeView;
	int mSubTreeLevel;

	float mSpacing; ///< Amount of space left empty between entries

	bool collapsed; ///< A tree view can be either collapsed or expanded to show its children items

public:

	/// Construct the tree view
	UITreeView();

	/// Set a new data model to this tree view
	void setModel(DataModel* dataModel);

	void itemClicked(Widget* node);

	/// Refresh the entire tree view structure, heavyweight, use with care
	void refreshStructure();

	/// Creates a new item with the ability for child items
	/// This is the only supported way to add a tree, to keep the API clean
	UITreeViewItem* createTree(const String& content, int id = 0);

	/// This will ensure positioning of the children
	void positionRows();
};


/**
\class UITreeNode
\brief The tree view is composed of nested lists of UIView and UITreeNode
*/
class NEPHILIM_API UITreeNode : public Widget
{
public:
	
	Color c = Color::Transparent;

	Widget* titleView = nullptr;

	/// Index of this subtree in the model, used to add model items to it
	int id;

	void setTitle(const String& content);

	void onPaint(UIPainter& painter);
};


NEPHILIM_NS_END
#endif // UITreeView_h__
