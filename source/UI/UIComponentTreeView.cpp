#include <Nephilim/UI/UIComponentTreeView.h>
#include <Nephilim/UI/UIComponentDebug.h>
#include <Nephilim/UIView.h>
#include <Nephilim/Logger.h>

NEPHILIM_NS_BEGIN

UIComponentTreeView::UIComponentTreeView()
: UIComponent()
, mSubTreeView(false)
, mSubTreeLevel(0)
{

}

/// This is called ONLY when a new item is added to the tree view
/// All items added are in the same level in the tree
void UIComponentTreeView::onChildAttached(UIView* child)
{
	Log("CHILD ADDED %s", child->getName().c_str());

	// Immediately set this children to its right spot
	float offsetY = 2.f;
	for(size_t i = 0; i < mParent->getChildCount(); ++i)
	{
		offsetY += mParent->getChild(i)->getSize().y + 2.f;
	}
	if(mSubTreeView)
		child->setRect(mParent->getPosition().x, mParent->getPosition().y + offsetY, mParent->getSize().x, 30.f);
	else
		child->setRect(mParent->getPosition().x + 10, mParent->getPosition().y + 10 + offsetY, mParent->getSize().x * 0.9f, 30.f);	

	//if(mSubTreeLevel == 1)
	//	child->addComponent(new UIComponentDebugColor(Color::Grass));
	if(mSubTreeLevel == 0)
		child->addComponent(new UIComponentDebugColor(Color::Blue));
	//if(mSubTreeLevel == 2)
	//	child->addComponent(new UIComponentDebugColor(Color::Bittersweet));

	// All children added to a tree view become TreeViewItem, whether they are collapsible or not
	child->addComponent(new UIComponentTreeViewItem());

	child->onNewChild.connect(sigc::bind(sigc::mem_fun(this, &UIComponentTreeView::onChildAddedToChild), child));

	// I want to be informed when any of the items change size to reposition things..
	child->onSizeChanged.connect(sigc::mem_fun(this, &UIComponentTreeView::updateItemPositions));

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

		Log("ADDED ITEM TO A SUBTREE, SUBTREE CONTAINER NOW %f", mParent->getSize().y);
	}
}

void UIComponentTreeView::updateItemPositions()
{
	if(!mSubTreeView)
	{
		Log("Updating top level positions");
	}

	float offset_y = 0.f;
	for(size_t i = 0; i < mParent->getChildCount(); ++i)
	{
		UIView* child = mParent->getChild(i);
		child->setPosition(child->getPosition().x, mParent->getPosition().y + offset_y);
		offset_y += child->getSize().y + 2.f;

		if(!mSubTreeView)
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

	subChild->onSizeChanged.connect(sigc::mem_fun(this, &UIComponentTreeView::updateItemPositions));

	if(child->getChildCount() == 1)
	{
		// Will now add a nested group (child = top level item (not header) subChild = group container)
		subChild->addComponent(new UIComponentTreeView());
		subChild->getComponent<UIComponentTreeView>()->mSubTreeView = true;
		subChild->getComponent<UIComponentTreeView>()->mSubTreeLevel = mSubTreeLevel + 1;
		
		subChild->setPosition(child->getPosition().x, child->getPosition().y + 30.f); // insert the container at the end of the header
		subChild->setSize(child->getSize().x, 0.f);

		// Hook to the child tree view so when it expands I my base item is notified and grows too
		subChild->getComponent<UIComponentTreeView>()->onChildItemGrow.connect(sigc::mem_fun(this, &UIComponentTreeView::growItem));

	}
	else
	{
		// subchild is the header of a subgroup, just position it
		subChild->mPadding.left = child->mPadding.left;
		subChild->setRect(child->getPosition().x, child->getPosition().y, child->getSize().x, 30.f);
		
		Log("Adding the item header %s", subChild->getName().c_str());

		// either way add expand the thing
		//child->setSize(child->getSize().x, child->getSize().y + 30.f);
	}


}

/// Grows one of the local items by an amount
void UIComponentTreeView::growItem(UIView* childItem, float amount)
{
	// Grow the child item
	childItem->setSize(childItem->getSize().x, childItem->getSize().y + amount);

	// 

}

void UIComponentTreeView::onRender(Renderer* renderer, UIView* view)
{
	// Draw a black background on the ROOT tree view
	if(mSubTreeLevel == 0)
	{
		RectangleShape back;
		back.setRect(view->getBounds());
		back.setColor(Color(36,36,36));
		renderer->draw(back);
	}
}

void UIComponentTreeViewItem::onRender(Renderer* renderer, UIView* view)
{
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