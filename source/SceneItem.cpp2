#ifndef MINIMAL_BUILD
#include "ParabolaCore/SceneItem.h"
#include "ParabolaCore/SceneNode.h"
#include "ParabolaCore/SceneRenderer.h"

#include <iostream>
using namespace std;

PARABOLA_NAMESPACE_BEGIN

/// Creates the scene item
SceneItem::SceneItem(){
	mySceneNodeParent = NULL;
};

/// Returns the name of the item
String SceneItem::name(){
	return myName;
};

/// Sets the name of the item
void SceneItem::setName(const String &name){
	myName = name;
};

/// Called when the item is attached to a node
void SceneItem::onAttach(){
	cout<<"Item attached"<<endl;
};

/// Get the SceneNode that owns this item, directly or indirectly.
SceneNode* SceneItem::getParentSceneNode(){
	return mySceneNodeParent;
};

/// Called when the scene item is supposed to render
void SceneItem::onRender(SceneRenderer* renderer){

};
PARABOLA_NAMESPACE_END

#endif