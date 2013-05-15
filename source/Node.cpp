#include "Nephilim/Node.h"
#include <iostream>

NEPHILIM_NS_BEGIN

/// Basic Node initialization from with a name
Node::Node(const String &name) : myParent(NULL){
	myName = name;
	myNodeType = SceneGraphNodeType::EmptyNode;
};

/// Virtual destructor
Node::~Node(){
	// when deleting this node, attempt to delete all the children.
	
};

/// Attempts to destroy the node, by deleting it
/// The task is only done if the node does not belong to any tree.
/// If it does belong to a tree, the tree will take care of its destruction.
void Node::destroy(){
	if(!myParent){
		// not inserted, will allow delete
		delete this;
	}
};


/// Attaches node to this Node's children
Node* Node::attachNode(Node* node){
	myChildren.push_back(node);
	node->myParent = this;
	return node;
};

/// Get the number of nodes this Node contains.
int Node::childCount(){
	return (int)myChildren.size();
};

/// Get the name of the node
String Node::name(){
	return myName;
};

/// Returns the parent of this node
Node* Node::parent(){
	return myParent;
};

/// Looks for a node with the name specified.
/// Returns NULL if the node was not found.
/// \note Please be careful when casting the node to another type, consider using dynamic_cast.
Node* Node::findNodeByName(const String &name){
	if(myName == name) return this; //found
	else
	{
		Node* n = NULL;
		for(NodeIterator it = myChildren.begin(); it != myChildren.end(); it++){
			n = (*it)->findNodeByName(name);
			if(n){
				return n; // a child found it, going back to the caller function
			}
		}
		return NULL;
	}
};

/// Looks for a node with the name specified.
/// Returns NULL if the node was not found.
/// \note Please be careful when casting the node to another type, consider using dynamic_cast.
Node* Node::findLocalNodeByName(const String &name){
	for(NodeIterator it = myChildren.begin(); it != myChildren.end(); it++){
		if((*it)->name() == name)
			return (*it);
	}
	return NULL;
};

/// Outputs the tree structure - debug
void Node::previewStructure(const String &data){
	std::cout<<data<<"> "<<myName<<"("<<getNodeType()<<")"<<std::endl;

	for(NodeIterator it = myChildren.begin(); it != myChildren.end(); it++){
		(*it)->previewStructure(data + "\t");
	}
};

/// Get the node type
int Node::getNodeType(){
	return myNodeType;
};

NEPHILIM_NS_END