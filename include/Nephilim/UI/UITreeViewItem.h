#ifndef UITreeViewItem_h__
#define UITreeViewItem_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Foundation/String.h>

#include <vector>

NEPHILIM_NS_BEGIN

class UIView;

/**
	\class UITreeViewItem
	\brief Hierarchy of nodes for a UITreeView

	This provides a solid hierarchic architecture for storing nodes in the tree,
	without concerning internal details of the UI system.

	Each item can be a node that contains sub items, or just a leaf node item.
*/
class NEPHILIM_API UITreeViewItem
{
public:

	/// Each item has its own widget, either a sub tree handler or the entry widget
	UIView* itemWidget = nullptr;

	/// The actual title of this item
	String content;

	/// Is a subtree or an item
	bool subtree;

	int id = -1;

	/// Our children, = 0 for leaf nodes
	std::vector<UITreeViewItem*> children;

	UITreeViewItem* parent;

public:
	/// Construct
	UITreeViewItem();

	/// Get the size of this item when the entire hierarchy is expanded
	/// Returns a constant for leaf nodes
	float getFullyExpandedSize();

	/// Get the current size of this item, counting in expanded and collapsed sub nodes and animation
	/// Returns a constant for leaf nodes
	float getCurrentSize();

	/// Get the height the node is currently taking 
	float getLocalSize();

	/// Returns how deep this item is in a hierarchy, 0 for root and so on
	int getDepth();

	/// Refresh the entire tree view structure, heavyweight, use with care
	void refreshStructure();

	/// Debug the entire hierarchy
	void debugLogHierarchy(int ind = 0);

	/// This is called by the children when they change size, to let the hierarchy stay organized
	void notifyChildChange(UITreeViewItem* caller);

	/// Find an item in the hierarchy with this id (used to match the model)
	UITreeViewItem* getItemFromId(int _id);

	/// Create a nested tree in this item
	UITreeViewItem* createTree(const String& title, int id);

	/// Create an item under this item with the give params
	UITreeViewItem* createItem(const String& title, int id);

};

NEPHILIM_NS_END
#endif // UITreeViewItem_h__
