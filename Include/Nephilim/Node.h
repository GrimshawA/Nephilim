#ifndef PARABOLA_BASENODE_H
#define PARABOLA_BASENODE_H

#include "Platform.h"
#include "Strings.h"

#include <vector>

PARABOLA_NAMESPACE_BEGIN

namespace SceneGraphNodeType{
	enum NodeTypes{
		EmptyNode = 0,
		SceneGraph,
		SceneLayer,		
		SceneNode,
		SceneItem
	};
}

/**

*/
class PARABOLA_API Node{
public:
	/// Basic Node initialization from with a name
	Node(const String &name);

	/// Virtual destructor
	virtual ~Node();

	/// Get the number of nodes this Node contains.
	int childCount();

	/// Get the name of the node
	String name();

	/// Returns the parent of this node
	virtual Node* parent();

	/// Attaches node to this Node's children
	/// Returns NULL if the attach failed.
	virtual Node* attachNode(Node* node);

	/// Looks for a node with the name specified in the whole tree
	/// Returns NULL if the node was not found.
	/// \note Please be careful when casting the node to another type, consider using dynamic_cast.
	virtual Node* findNodeByName(const String &name);

	/// Looks for a node with the name specified within the local child list.
	/// Returns NULL if the node was not found.
	/// \note Please be careful when casting the node to another type, consider using dynamic_cast.
	virtual Node* findLocalNodeByName(const String &name);

	/// Attempts to destroy the node, by deleting it
	/// The task is only done if the node does not belong to any tree.
	/// If it does belong to a tree, the tree will take care of its destruction.
	virtual void destroy();

	/// Outputs the tree structure - debug
	virtual void previewStructure(const String &data);

	/// Get the node type
	int getNodeType();

protected:
	typedef std::vector<Node*>::iterator NodeIterator;
	//// Nodes children
	std::vector<Node*> myChildren;	
	int myNodeType;

private:
	/// Node name
	String myName;
	Node* myParent;
	
};

PARABOLA_NAMESPACE_END
#endif