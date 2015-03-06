#include <Nephilim/UI/UITreeViewItem.h>
#include <Nephilim/UI/UITreeView.h>
#include <Nephilim/UI/UIToolkit.h>

NEPHILIM_NS_BEGIN

/// Construct
UITreeViewItem::UITreeViewItem()
: parent(nullptr)
{

}

/// Debug the entire hierarchy
void UITreeViewItem::debugLogHierarchy(int ind)
{
	String indstring;
	for (int i = 0; i < ind; ++i)
		indstring += "\t";

	Log("%s'%s' with %d children. Measure %f (at %f)", indstring.c_str(), content.c_str(), children.size(), getLocalSize(), itemWidget->position.y);

	for (auto i : children)
	{
		i->debugLogHierarchy(ind + 1);
	}
}

/// Find an item in the hierarchy with this id (used to match the model)
UITreeViewItem* UITreeViewItem::getItemFromId(int _id)
{
	if (id == _id)
		return this;

	for (auto item : children)
	{
		if (item->getItemFromId(_id))
			return item->getItemFromId(_id);
	}

	return nullptr;
}

/// Create a nested tree in this item
UITreeViewItem* UITreeViewItem::createTree(const String& title, int id)
{
	UITreeViewItem* treeViewItem = new UITreeViewItem;
	treeViewItem->id = id;
	treeViewItem->content = title;
	treeViewItem->parent = this;
	children.push_back(treeViewItem);

	UITreeNode* widget = itemWidget->createChild<UITreeNode>("tree");
	widget->setFlag(UIFlag::FILL_PARENT_WIDTH);
	widget->setRect(0.f, 20.f, itemWidget->width(), 20.f);
	//widget->m_clipChildren = true;
	widget->mPadding.left = 30.f * (getDepth() + 1);
	widget->id = id;
	widget->setTitle(title);
	widget->titleView->mPadding.left = 30.f * (getDepth() + 1);
	widget->c = Color(40 * id, 50 * id, 20 * id);
	treeViewItem->itemWidget = widget;

	// Were there previous items in this node?
	if (children.size() > 1)
	{
		UIView* previousWidget = children[children.size() - 2]->itemWidget;
		widget->setPosition(Vector2D(0.f, previousWidget->getPosition().y + previousWidget->height()));
	}

	// grow a bit this container subtree and notify parent we grown
	itemWidget->setSize(itemWidget->width(), itemWidget->height() + 20.f);
	if (parent)
	{
		parent->notifyChildChange(this);
	}

	return treeViewItem;
}

/// Create an item under this item with the give params
UITreeViewItem* UITreeViewItem::createItem(const String& title, int id)
{
	UITreeViewItem* treeViewItem = new UITreeViewItem;
	treeViewItem->id = id;
	treeViewItem->content = title;
	treeViewItem->parent = this;
	children.push_back(treeViewItem);

	UIView* item = itemWidget->createChild("item");
	//item->addController(new UIComponentDebugColor(Color::Transparent));
	//item->addController(new UITextNode(title, UITextNode::Left, UITextNode::Center));
	item->setFlag(UIFlag::FILL_PARENT_WIDTH);
	// This is a nested item, which means it has to start at 20.f to compensate the title
	item->setRect(0.f, 20.f, itemWidget->width(), 20.f); // immutable dimensions, just the y position changes
	item->mPadding.left = 30.f * (getDepth() + 1);
	treeViewItem->itemWidget = item;

	// add a tiny icon as a sub of the item
	UIView* icon = item->createChild("icon");
	icon->setSize(20.f, 20.f);
	icon->setPosition(0.f, 0.f);
	//icon->addController(new UIComponentImage("./Core/EditorAssets/person14.png"));

	// Were there previous items in this node?
	if (children.size() > 1)
	{
		UIView* previousWidget = children[children.size() - 2]->itemWidget;
		item->setPosition(Vector2D(0.f, previousWidget->getPosition().y + previousWidget->height()));
	}


	//item->onClick.connect(sigc::bind(sigc::mem_fun(this, &UITreeView::itemClicked), item));

	// grow a bit this container subtree and notify parent we grown
	itemWidget->setSize(itemWidget->width(), itemWidget->height() + 20.f);
	if (parent)
	{
		parent->notifyChildChange(this);
	}

	return treeViewItem;
}

/// Get the size of this item when the entire hierarchy is expanded
/// Returns a constant for leaf nodes
float UITreeViewItem::getFullyExpandedSize()
{
	if (children.empty())
		return 20.f;
	else
	{
		float _s = 20.f; // not a leaf, will always need extra for the title
		for (auto c : children)
		{
			_s += c->getFullyExpandedSize();
		}
		return _s;
	}
}

/// Get the current size of this item, counting in expanded and collapsed sub nodes and animation
/// Returns a constant for leaf nodes
float UITreeViewItem::getCurrentSize()
{
	if (children.empty())
		return 20.f;
	else
	{
		return 20.f;
	}
}

/// Get the height the node is currently taking 
float UITreeViewItem::getLocalSize()
{
	return itemWidget->height();
}


/// Returns how deep this item is in a hierarchy, 0 for root and so on
int UITreeViewItem::getDepth()
{
	if (!parent)
		return 0;
	else
	{
		return parent->getDepth() + 1;
	}
}

/// Refresh the entire tree view structure, heavyweight, use with care
void UITreeViewItem::refreshStructure()
{
	/// Nothing to do to a leaf node, it stays 20.f
	if (children.empty())
		return;

	for (auto c : children)
	{
		c->itemWidget->setSize(c->itemWidget->width(), c->getFullyExpandedSize());
	}

	float pos_y = 20.f;
	for (auto c : children)
	{
		UIView* child = c->itemWidget;

		child->position.y = pos_y;

		pos_y += child->height();
	}

	for (auto c : children)
	{
		c->refreshStructure();
	}
}

/// This is called by the children when they change size, to let the hierarchy stay organized
void UITreeViewItem::notifyChildChange(UITreeViewItem* caller)
{
	/// If this function is being called, we are a category node with children
	if (caller)
	{

		// Put all the children UIWidget of this category layouted ( including the title )
		float pos_y = 0.f;

		for (std::size_t i = 0; i < children.size(); ++i)
		{
			UIView* child = children[i]->itemWidget;

			//child->position.y = pos_y;
			
			pos_y += child->height();
		}

		/// Each item is always the sum of its children sizes
		itemWidget->setSize(itemWidget->width(), getFullyExpandedSize());
	}


	if (parent)
		notifyChildChange(this);
}

NEPHILIM_NS_END