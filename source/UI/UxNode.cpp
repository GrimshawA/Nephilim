#include <Nephilim/UI/UxNode.h>

NEPHILIM_NS_BEGIN

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

NEPHILIM_NS_END
