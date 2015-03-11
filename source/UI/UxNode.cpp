#include <Nephilim/UI/UxNode.h>

NEPHILIM_NS_BEGIN

/// Just default initialization of the node
UxNode::UxNode()
: mParent(nullptr)
{

}

/// Construct directly as another node child
UxNode::UxNode(UxNode* _parent)
{
	mParent = _parent;
	mParent->mChildren.push_back(this);
}

/// Destructor
UxNode::~UxNode()
{

}

/// Just a getter for the core
UICore* UxNode::getCore()
{
	return _core;
}

/// Tells the object to set itself up if needed
void UxNode::onSetup()
{
}

/// Dispatches an event into the hierarchy
void UxNode::dispatch(const UxEvent& event)
{
}

/// Get the object name of this node
const char* UxNode::getName()
{
	return "UxNode";
}

/// Get the class name of this node
const char* UxNode::getClassName()
{
	return "UxNode";
}

/// Every node is the most elemental class in the UX hierarchy
/// This is the primary render function called on a node, causing it to draw itself in anyway
void UxNode::render(UxRenderState renderState)
{
	for (auto c : mChildren)
	{
		c->render(renderState);
	}
}

NEPHILIM_NS_END
