
#ifndef MINIMAL_BUILD
#include "ParabolaCore/SceneLayer.h"
#include "ParabolaCore/SceneNode.h"
#include "ParabolaCore/SceneRenderer.h"
#include "ParabolaCore/Text.h"
#include "ParabolaCore/SceneGraph.h"
#include "ParabolaCore/KinesisWorld.h"

#include <iostream>
using namespace std;

PARABOLA_NAMESPACE_BEGIN
/// Creates the named scene layer~- only the SceneGraph must instance these. 
SceneLayer::SceneLayer(const String &name) : Node(name), myEntityManager(new EntityManager()){
	mySimulation = NULL;
	myNodeType = SceneGraphNodeType::SceneLayer;
};

/// Re-implementation of attachNode to avoid attaching invalid node types.
Node* SceneLayer::attachNode(Node* node){
	return Node::attachNode(node);
};

/// Creates a new child scene node
SceneNode* SceneLayer::createSceneNode(const String &name){
	SceneNode *node = new SceneNode(name);
	node = (SceneNode*)attachNode(node);
	return node;
};


/// Creates a new entity manager
EntityManager* SceneLayer::getEntityManager(){
	return myEntityManager.get();
};

/// Assigns itself a previously created simulation
bool SceneLayer::useKinesisWorld(const String &name, bool requestOwnership){
	SceneGraph *graph = (SceneGraph*)parent();
	if(graph){
		mySimulation = graph->requestKinesisWorld(name, this, requestOwnership);
	}
	else{
		mySimulation = NULL;
	}

	return (mySimulation != NULL);
};

/// Returns the associated physics world, or NULL if none exists
KinesisWorld* SceneLayer::getKinesisWorld(){
	if(mySimulation){
		return mySimulation->resource;
	}
	else
		return NULL;
};

/// Updates the entire graph state by elapsedTime seconds
void SceneLayer::updateGraph(float elapsedTime){
	//draw physics
	if(mySimulation && mySimulation->owner == this){		
		mySimulation->resource->update(elapsedTime);
	}

	for(NodeIterator it = myChildren.begin(); it != myChildren.end(); it++){
		static_cast<SceneNode*>(*it)->update(elapsedTime);
	};
};

/// Renders the layer
void SceneLayer::render(SceneRenderer* renderer){
	renderer->draw(Text(name(),120.f,10.f*name().size()));

	//renderer->renderTarget()->PushGLStates();

	//draw physics
	if(mySimulation && mySimulation->owner == this){
		//cout<<"draw physc"<<endl;
		mySimulation->resource->drawDebug(renderer);
	}

	
	/*renderer->renderTarget()->ResetGLStates();
	for(NodeIterator it = myChildren.begin(); it != myChildren.end(); it++){
		static_cast<SceneNode*>(*it)->render(renderer);
	};
	renderer->renderTarget()->PopGLStates();*/
};

PARABOLA_NAMESPACE_END

#endif