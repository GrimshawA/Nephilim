
#ifndef MINIMAL_BUILD
#include "ParabolaCore/SceneNode.h"
#include "ParabolaCore/SceneItem.h"
#include "ParabolaCore/Entity.h"
#include "ParabolaCore/SceneRenderer.h"

#include <iostream>
using namespace std;

PARABOLA_NAMESPACE_BEGIN

/// Creates a scene node
SceneNode::SceneNode() : Node(""){
	myUpdateState = true;
	myNodeType = SceneGraphNodeType::SceneNode;
};

/// Creates a default named Scene Node
SceneNode::SceneNode(const String &name) : Node(name){
	myUpdateState = true;
	myNodeType = SceneGraphNodeType::SceneNode;
};

/// Creates a new child scene node
SceneNode* SceneNode::createSceneNode(const String &name){
	SceneNode *node = new SceneNode(name);
	node = (SceneNode*)attachNode(node);
	return node;
};




/// Sets the position of this node, adjusting its children as well
void SceneNode::setPosition(float x, float y){
	myLocalPosition.x = x;
	myLocalPosition.y = y;
};

/// Get global position of this node
Vec2f SceneNode::getGlobalPosition(){
	Vec2f globalPosition(0.f,0.f);

	if(dynamic_cast<SceneNode*>(parent())){
		//there is parent
		globalPosition += ((SceneNode*)parent())->getGlobalPosition();
	}

	return globalPosition + myLocalPosition;
};

/// Get the layer this node is inserted into
SceneLayer* SceneNode::getLayerNode(){
	if(!parent())return NULL;

	if(parent()->getNodeType() == SceneGraphNodeType::SceneLayer){
		
		return (SceneLayer*)parent();
	}
	else if(parent()->getNodeType() == SceneGraphNodeType::SceneNode){
		return ((SceneNode*)parent())->getLayerNode();
	}
	else return NULL;
};

/// Get local position of this node
Vec2f SceneNode::getLocalPosition(){
	return myLocalPosition;
};

/// Updates the node and its children
void SceneNode::update(float elapsedTime){
	// my own updates
	//std::cout<<"Node update: "<<name()<<std::endl;

	if(myUpdateState){
		for(NodeIterator it = myChildren.begin(); it != myChildren.end(); it++){
			static_cast<SceneNode*>(*it)->update(elapsedTime);
		};
	}
};

/// Updates the node and its children
void SceneNode::render(SceneRenderer *renderer){
	/*sf::CircleShape c;
	c.SetFillColor(sf::Color::Red);
	c.SetRadius(4);
	c.SetPosition(getGlobalPosition().x, getGlobalPosition().y);*/
	//renderer->draw(c);

	for(ItemIterator it = myItems.begin(); it != myItems.end(); it++){
		(*it)->onRender(renderer);
	}

	for(NodeIterator it = myChildren.begin(); it != myChildren.end(); it++){
		static_cast<SceneNode*>(*it)->render(renderer);
	};
};

/// Attaches an item to this node, such as an entity, a camera, etc
bool SceneNode::attachItem(SceneItem *item){
	myItems.push_back(item);
	item->mySceneNodeParent = this;
	item->onAttach();
	return true;
};


/// Debug
void SceneNode::previewStructure(const String &data){
	
	Node::previewStructure(data);
	String entities;
	for(ItemIterator it = myItems.begin(); it != myItems.end(); it++){
		if(!entities.empty())entities += ",";
		entities += static_cast<Entity*>(*it)->name();
	};

	std::cout<<data<<"  :"<<" Entities("<<entities<<")"<<std::endl;
};

PARABOLA_NAMESPACE_END

#endif