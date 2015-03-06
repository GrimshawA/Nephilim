#include <Nephilim/UI/UITreeView.h>
#include <Nephilim/UI/UITreeViewItem.h>
#include <Nephilim/UI/UIDebugWidget.h>
#include <Nephilim/UI/UITextNode.h>

#include <Nephilim/Foundation/Logging.h>
#include <Nephilim/Foundation/DataModel.h>
#include <Nephilim/Foundation/Path.h>

NEPHILIM_NS_BEGIN

UITreeView::UITreeView()
: UIView()
, mSubTreeView(false)
, mSubTreeLevel(0)
, mLineHeight(30.f)
, collapsed(false)
, mSpacing(2.f)
{

}

/// Set a new data model to this tree view
void UITreeView::setModel(DataModel* dataModel)
{
	_dataModel = dataModel;

	// First thing we want is to put this model under its own root UITreeNode
	UITreeViewItem* rootItem = createTree("Root", -1);

	// todo: detach from file models, to work with ANY model
	// For each row (dir or file) in the file system, we will make one TreeViewItem and fill every stuff needed
	for (int i = 0; i < _dataModel->rows(); ++i)
	{
		bool isFile;
		Path p;
		String name;
		int parentRow;

		name = _dataModel->data(i, 0).toString();
		isFile = _dataModel->data(i, 1).toBool();
		p = _dataModel->data(i, 2).toString();
		parentRow = _dataModel->data(i, 3).toInt();

		// Add a new sub tree
		if (!isFile)
		{
			/// We add our directory to the rootItem with the data model id
			rootItem->createTree(name, i);
		}
		else
		{
			/// Add an item to a subtree
			if (parentRow == -1)
			{
				/// This entry is a file, which belongs under the root item
				rootItem->createItem(name, i);
			}
			else
			{
				/// This entry is a file, and not at top level so we need to find its rightful tree
				UITreeViewItem* category = rootItem->getItemFromId(parentRow);
				if (category)
				{
					category->createItem(name, i);
				}
				else
				{
					Log("Failed to insert item %s into row %d ", name.c_str(), parentRow);
				}
			}
		}
	}
}


void UITreeView::itemClicked(UIView* node)
{
	for (std::size_t i = 0; i < selectedItems.size(); ++i)
	{
		selectedItems[i]->getComponent<UIDebugWidget>()->mColor = Color::Transparent;
	}
	selectedItems.clear();

	node->getComponent<UIDebugWidget>()->mColor = Color::Blue;
	selectedItems.push_back(node);
}

UITreeViewItem* UITreeView::createTree(const String& content, int id)
{
	// We add a child item, who is a subtree itself. It has its own subtree manager component


	// for now add a NavyBlue subtree area
	UITreeNode* item = createChild<UITreeNode>("tree");
	item->setFlag(UIFlag::FILL_PARENT_WIDTH);
	item->setRect(0.f, 0.f, width(), 20.f);
	//item->m_clipChildren = true;
	item->mPadding.left = 20.f;
	item->id = id;
	item->setTitle(content);

	// Create the item that manages things internally
	UITreeViewItem* treeViewItem = new UITreeViewItem;
	treeViewItem->itemWidget = item;
	treeViewItem->content = content;
	treeViewItem->id = id;
	items.push_back(treeViewItem);

	return treeViewItem;
}

/// Refresh the entire tree view structure, heavyweight, use with care
void UITreeView::refreshStructure()
{
	for (auto item : items)
	{
		item->refreshStructure();
	}
}

//////////////////////////////////////////////////////////////////////////

void UITreeNode::setTitle(const String& content)
{
	if (!titleView)
	{
		titleView = createChild("title");
		//titleView->addController(new UIDebugWidget(Color::NavyBlue));
///		titleView->addController(new UITextNode(content, UITextNode::Left, UITextNode::Left));
		titleView->setSize(width(), 20.f);
		titleView->setPosition(0.f, 0.f);
		titleView->mPadding.left = 20.f;
	}
}

void UITreeNode::onPaint(UIPainter& painter)
{
	painter.setFillColor(Color::Red);
	painter.drawRect(titleView->getRect());
	//painter.drawText("SAD");
}



NEPHILIM_NS_END