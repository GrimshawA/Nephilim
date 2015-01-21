#include <Nephilim/UI/UIComponentTreeView.h>
#include <Nephilim/UI/UIComponentDebug.h>
#include <Nephilim/UI/UIComponentText.h>
#include <Nephilim/UI/UIComponentImage.h>
#include <Nephilim/UI/UIView.h>
#include <Nephilim/Foundation/Logging.h>

NEPHILIM_NS_BEGIN

UIComponentTreeView::UIComponentTreeView()
: UIComponent()
, mSubTreeView(false)
, mSubTreeLevel(0)
, mLineHeight(30.f)
, collapsed(false)
, mSpacing(2.f)
{

}

void UIComponentTreeView::addItem(const String& content)
{
	UIView* item = mParent->createChild("item");
	item->addComponent(new UIComponentDebugColor(Color::Transparent));
	item->addComponent(new UIComponentText(content, UIComponentText::Left, UIComponentText::Center));
	item->setFlag(UIFlag::FILL_PARENT_WIDTH);
	item->setRect(0.f, 0.f, mParent->size.x, 20.f);
	item->mPadding.left = 20.f;

	// add a tiny icon
	UIView* icon = item->createChild("icon");
	icon->setSize(20.f, 20.f);
	icon->setPosition(0.f, 0.f);
	icon->addComponent(new UIComponentImage("./Core/EditorAssets/person14.png"));

	item->onClick.connect(sigc::bind(sigc::mem_fun(this, &UIComponentTreeView::itemClicked), item));

	positionRows();
}

void UIComponentTreeView::itemClicked(UIView* node)
{
	for (std::size_t i = 0; i < selectedItems.size(); ++i)
	{
		selectedItems[i]->getComponent<UIComponentDebugColor>()->mColor = Color::Transparent;
	}
	selectedItems.clear();

	node->getComponent<UIComponentDebugColor>()->mColor = Color::Blue;
	selectedItems.push_back(node);
}


void UIComponentTreeView::addTree(const String& content)
{
	// We add a child item, who is a subtree itself. It has its own subtree manager component


	// for now add a NavyBlue subtree area
	UIView* item = mParent->createChild("tree");
	//item->addComponent(new UIComponentDebugColor(Color::NavyBlue));
	//item->addComponent(new UIComponentText(content));
	item->setFlag(UIFlag::FILL_PARENT_WIDTH);
	item->addComponent(new UIComponentSubTree());
	item->setRect(0.f, 0.f, mParent->size.x, 20.f);
	item->m_clipChildren = true;
	item->mPadding.left = 20.f;

	// add a tiny icon
	/*UIView* icon = item->createChild("icon");
	icon->setSize(10.f, 10.f);
	icon->setPosition(5.f, 6.f);
	icon->addComponent(new UIComponentImage("./Core/EditorAssets/folder5.png"));*/

	UIComponentSubTree* subTree = item->getComponent<UIComponentSubTree>();
	subTree->addItem(content); // first one added is the title.
	subTree->addItem("Actor 1");
	subTree->addItem("Actor 2");
	subTree->addItem("Actor 3");

	// Ensure the root level stays positioned, after the additions
	positionRows();
}

void UIComponentTreeView::positionRows()
{
	float pos_y = 0.f;

	for (std::size_t i = 0; i < mParent->getChildCount(); ++i)
	{
		UIView* child = mParent->getChild(i);
		child->position.y = pos_y;

		pos_y += child->size.y + 1.f;
	}
}

/// This is called ONLY when a new item is added to the tree view
/// All items added are in the same level in the tree
void UIComponentTreeView::onChildAttached(UIView* child)
{
	/*Log("CHILD ADDED %s", child->getName().c_str());

	// Immediately set this children to its right spot
	float offsetY = 0.f;
	for(size_t i = 0; i < mParent->getChildCount(); ++i)
	{
		offsetY += mParent->getChild(i)->getSize().y + 2.f;
	}
	if(mSubTreeView)
		child->setRect(mParent->getPosition().x, mParent->getPosition().y + offsetY, mParent->getSize().x, mLineHeight);
	else
		child->setRect(mParent->getPosition().x, mParent->getPosition().y + offsetY, mParent->getSize().x, mLineHeight);	

	//if(mSubTreeLevel == 1)
	//	child->addComponent(new UIComponentDebugColor(Color::Grass));
	//if(mSubTreeLevel == 0)
		//child->addComponent(new UIComponentDebugColor(Color::Blue));
	//if(mSubTreeLevel == 2)
	//	child->addComponent(new UIComponentDebugColor(Color::Bittersweet));

	// All children added to a tree view become TreeViewItem, whether they are collapsible or not
	child->addComponent(new UIComponentTreeViewItem());

	child->onNewChild.connect(sigc::bind(sigc::mem_fun(this, &UIComponentTreeView::onChildAddedToChild), child));

	// I want to be informed when any of the items change size to reposition things..
	//child->onSizeChanged.connect(sigc::mem_fun(this, &UIComponentTreeView::updateItemPositions));

	child->mPadding.left = (mSubTreeLevel + 1) * 20.f;

	// If this is a subgroup tree view, needs to expand and shrink
	if(mSubTreeView)
	{
		// Grow the container to fit one more item
		mParent->setSize(mParent->getSize().x, mParent->getSize().y + 32.f);

		// Grow the actual item too which contains this container
		mParent->getParent()->setSize(mParent->getParent()->getSize().x, mParent->getParent()->getSize().y + 32.f);

		// For level 1 tree views, there is no need to update the parent, but for any deeper, the increase needs to propagate
		int treeLevel = mSubTreeLevel;
		UIView* subTreeContainer = mParent;
		UIView* itemContainer = subTreeContainer->getParent();
		while(treeLevel >= 1)
		{
			// propagate the growth
			subTreeContainer = itemContainer->getParent();
			itemContainer = subTreeContainer->getParent();

			// Grow the container to fit one more item
			subTreeContainer->setSize(subTreeContainer->getSize().x, subTreeContainer->getSize().y + 32.f);

			// Grow the actual item too which contains this container
			itemContainer->getParent()->setSize(itemContainer->getParent()->getSize().x, itemContainer->getParent()->getSize().y + 32.f);

			treeLevel--;
		}

		//Log("ADDED ITEM TO A SUBTREE, SUBTREE CONTAINER NOW %f", mParent->getSize().y);
	}*/
}

/// Toggle will expand/collapse the tree view
void UIComponentTreeView::toggle()
{
	if(collapsed)
	{
		Log("Expanding a tree container. Total size of %d children", mParent->getChildCount());
		float allItemsSize = 0.f;
		for(size_t i = 0; i < mParent->getChildCount(); ++i)
		{
			allItemsSize += getItemSize(i).y;
			Log("Child %i rect(%f,%f,%f,%f)", i, mParent->getChild(i)->getPosition().x, mParent->getChild(i)->getPosition().y, mParent->getChild(i)->getSize().x, mParent->getChild(i)->getSize().y);
		}


		mParent->setSize(mParent->getSize().x, getSize().y);
		collapsed = false;
	}
	else
	{
		mParent->setSize(mParent->getSize().x, 0.f);
		collapsed = true;
	}
}

void UIComponentTreeView::updateItemPositions()
{
	float offset_y = 0.f;
	for(size_t i = 0; i < mParent->getChildCount(); ++i)
	{
		UIView* child = mParent->getChild(i);
		child->setPosition(child->getPosition().x, mParent->getPosition().y + offset_y);

		offset_y += child->getSize().y + 2.f;

		if(mSubTreeView)
		{
			Log("Child %d sizeY %f stays at %f", i, child->getSize().y, child->getPosition().y);
		}
	}
}


/// Whenever a child is added to any of this UIView's children
/// we need to act upon it
void UIComponentTreeView::onChildAddedToChild(UIView* subChild, UIView* child)
{
	Log("CHILD OF CHILD %s %s", subChild->getName().c_str(), child->getName().c_str());

	//subChild->onSizeChanged.connect(sigc::mem_fun(this, &UIComponentTreeView::updateItemPositions));

	if(child->getChildCount() == 1)
	{
		// Will now add a nested group (child = top level item (not header) subChild = group container)
		subChild->addComponent(new UIComponentTreeView());
		subChild->getComponent<UIComponentTreeView>()->mSubTreeView = true;
		subChild->getComponent<UIComponentTreeView>()->mSubTreeLevel = mSubTreeLevel + 1;

		//subChild->addComponent(new UIComponentDebugColor(Color::Blue));

		subChild->setPosition(child->getPosition().x, child->getPosition().y + 30.f); // insert the container at the end of the header
		subChild->setSize(child->getSize().x, 0.f);
	}
	else // THE HEADER
	{
		// subchild is the header of a subgroup, just position it
		subChild->mPadding.left = (mSubTreeLevel + 1) * 20.f;
		subChild->setRect(child->getPosition().x, child->getPosition().y, child->getSize().x, 30.f);
		//subChild->addComponent(new UIComponentDebugColor(Color::Blue));
		subChild->onClick.connect(sigc::bind(sigc::mem_fun(this, &UIComponentTreeView::toggleItem), child));
	}
}

/// Expands/Collapses the child item if it exists
void UIComponentTreeView::toggleItem(UIView* item)
{
	for(std::vector<UIView*>::iterator it = mParent->m_children.begin(); it != mParent->m_children.end(); ++it)
	{
		if((*it) == item)
		{
			UIComponentTreeViewItem* treeItem = item->getComponent<UIComponentTreeViewItem>();
			if(treeItem)
			{
				treeItem->toggle();
			}
		}
	}
}

/// Recomputes all sizes and positions for the entire hierarchy (can be heavy)
void UIComponentTreeView::recomputeTree()
{
	// No children in this subtree
	if(mParent->getChildCount() == 0)
	{
		mParent->setSize(mParent->getSize().x, 0.f);
		return;
	}


	float totalTreeSize = 0.f;

	// First step is to get final sizes on all elements
	for(size_t i = 0; i < mParent->getChildCount(); ++i)
	{
		vec2 s = computeChildSize(i);
		mParent->getChild(i)->setSize(s.x, s.y);

		totalTreeSize += s.y + 2.f;
	}

	// Second step to reposition everything to its place
	updateItemPositions();

	if(mSubTreeLevel > 0 && mParent->getChildCount() > 0)
	{
		mParent->setSize(mParent->getSize().x, totalTreeSize);

		// Set the actual item entry too to the right size
		mParent->getParent()->setSize(mParent->getParent()->getSize().x, totalTreeSize + 30.f);
	}

	Log("RECOMPUTING TREE LEVEL: %d", mSubTreeLevel);
}

/// Get current size of this subtree container
vec2 UIComponentTreeView::getSize()
{
	float height = 0.f;
	for(size_t i = 0; i < mParent->getChildCount(); ++i)
	{
		height += getItemSize(i).y + mSpacing;
	}

	return vec2(mParent->getSize().x, height);
}

/// Get the current size of the <index> child item
vec2 UIComponentTreeView::getItemSize(int index)
{
	if(isSubTree(index))
	{
		// This item is an arbitrarily complex tree, need to get that tree header + spacing + each item size
		UIView* subTreeContainer = mParent->getChild(index)->getChild(1);
		UIComponentTreeView* subTree = mParent->getChild(index)->getChild(1)->getComponent<UIComponentTreeView>();


		// A subtree item has size of the header + spacing + container of items
		return subTree->getSize() + vec2(0.f, mLineHeight + mSpacing);
	}
	else
	{
		//Log("simple item");

		// This item is a individual "file" and is only a fixed height
		return vec2(mParent->getChild(index)->getSize().x, mLineHeight);
	}
}

vec2 UIComponentTreeView::computeChildSize(int index)
{
	// is it a individual item? needs adjustments to support children of individual items
	if(mParent->getChild(index)->getChildCount() == 0)
	{
		return vec2(mParent->getSize().x, mLineHeight);
	}
	else // subgroup
	{
		UIComponentTreeView* childTreeView = mParent->getChild(index)->getChild(1)->getComponent<UIComponentTreeView>();
		if(childTreeView)
		{
			// Tell the child tree to recompute itself
			childTreeView->recomputeTree();
			/*
			float totalItemSize = 30.f;
			for(size_t i = 0; i < childTreeView->mParent->getChildCount(); ++i)
			{
				totalItemSize += childTreeView->computeChildSize(i).y;
			}

			// sum total spacing between each item
			totalItemSize += childTreeView->mParent->getChildCount() * 2.f;

			return vec2(mParent->getSize().x, totalItemSize);*/

			return vec2(mParent->getSize().x, childTreeView->mParent->getSize().y + 30.f);
		}
	}

	return vec2();
}

/// Check if any of the children items are expandible (subtrees)
bool UIComponentTreeView::isSubTree(int index)
{
	UIView* item = mParent->getChild(index);

	for(size_t i = 0; i < item->getChildCount(); ++i)
	{
		if(item->getChild(i)->getComponent<UIComponentTreeView>())
			return true;
	}

	return false;
}


////////////////////////////////////////////////////////////////////////// UICOMPONENTSUBTREE

void UIComponentSubTree::addItem(const String& content)
{
	UIView* item = mParent->createChild("item");
	//item->addComponent(new UIComponentDebugColor(Color::Red));
	item->addComponent(new UIComponentText(content, UIComponentText::Left, UIComponentText::Center));
	item->setRect(0.f, 0.f, mParent->size.x, 20.f);
	item->setFlag(UIFlag::FILL_PARENT_WIDTH);
	if (mParent->getChildCount() == 1)
	{
		item->mPadding.left += mParent->mPadding.left;
	}
	else
	{
		item->mPadding.left += mParent->mPadding.left + 20.f;
	}

	positionRows();
}

void UIComponentSubTree::positionRows()
{
	float pos_y = 0.f;

	for (std::size_t i = 0; i < mParent->getChildCount(); ++i)
	{
		UIView* child = mParent->getChild(i);
		child->position.y = pos_y;

		pos_y += child->size.y + 1.f;
	}

	// Parent must become the total size now 
	mParent->size.y = pos_y ;
}

//////////////////////////////////////////////////////////////////////////



void UIComponentTreeViewItem::toggle()
{
	UIComponentTreeView* treeView = NULL;
	UIView* treeViewContainer = NULL;
	for(std::vector<UIView*>::iterator it = mParent->m_children.begin(); it != mParent->m_children.end(); ++it)
	{
		if(!treeView)
			treeView = (*it)->getComponent<UIComponentTreeView>();
		if(treeView)
			treeViewContainer = treeView->mParent;
	}

	// This item is a valid tree view container, can toggle
	if(treeView)
	{
		//treeViewContainer->m_clipChildren = true;
		treeView->toggle();		
	}
}

void UIComponentTreeViewItem::onRender(GraphicsDevice* renderer, UIView* view)
{
	// Render this item full size

	/*RectangleShape back;
	back.setRect(view->getBounds());
	back.setColor(Color::Red);
	renderer->draw(back);*/

	// Render a little expandable flag if it applies
	if(mParent->getChildCount() > 0)
	{
		RectangleShape back;
		back.setRect(mParent->getChild(0)->getBounds());
		back.setSize(5.f, back.getSize().y);
		back.setColor(Color::Red);
		renderer->draw(back);
	}
}


NEPHILIM_NS_END