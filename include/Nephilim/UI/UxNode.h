#ifndef NephilimUIObject_h__
#define NephilimUIObject_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Foundation/Object.h>
#include <Nephilim/UI/UxRenderState.h>

#include <sigc++/sigc++.h>
#include <vector>

NEPHILIM_NS_BEGIN

class UICore;
class GraphicsDevice;
class UxEvent;

/**
	\class UxNode
	\brief Every node in the big user experience graph is a UxNode

	Every object in the UX graph is a UxNode, and this is where the hierarchy is formed
*/
class NEPHILIM_API UxNode : public Object, public sigc::trackable
{
public:
	/// Every UIObject needs to reference a UICore to function properly
	/// It is the resource provider as well as other utilities
	/// This is not an owning reference, it must be destroyed somewhere.
	UICore*                _core = nullptr;

	/// Children of this node
	std::vector<UxNode*> mChildren;

	typedef std::vector<UxNode*>::iterator ChildrenIterator;

	/// Usually, an UxNode object has a parent node
	UxNode* mParent;

public:

	/// Construct with default initialization of the node
	UxNode();

	/// Construct directly as another node child
	UxNode(UxNode* _parent);

	/// Destructor
	virtual ~UxNode();

	/// Just a getter for the core
	UICore* getCore();

	/// Get the object name of this node
	virtual const char* getName();

	/// Get the class name of this node
	virtual const char* getClassName();

	/// Tells the object to set itself up if needed
	virtual void onSetup();

	/// Dispatches an event into the hierarchy
	virtual void dispatch(const UxEvent& event);

	/// Every node is the most elemental class in the UX hierarchy
	/// This is the primary render function called on a node, causing it to draw itself in anyway
	virtual void render(UxRenderState renderState);


	template<typename T, typename ...Args>
	static T* Create(UxNode* base, Args&& ...args);

	template<typename T>
	static T* Create2(UxNode* base);
};

template<typename T, typename ...Args>
T* UxNode::Create(UxNode* base, Args&& ...args)
{
	UxNode* node = new T(std::forward<Args>(args)... );
	base->mChildren.push_back(node);
	return static_cast<T*>(node);
}

template<typename T>
T* UxNode::Create2(UxNode* base)
{
	UxNode* node = new T();
	base->mChildren.push_back(node);
	return static_cast<T*>(node);
}

NEPHILIM_NS_END
#endif // NephilimUIObject_h__
