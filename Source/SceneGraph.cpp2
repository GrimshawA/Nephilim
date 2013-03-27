#include "ParabolaCore/SceneGraph.h"
/*#include "ParabolaCore/SceneRenderer.h"
#include "ParabolaCore/Text.h"
#include "ParabolaCore/KinesisWorld.h"
*/
#include <iostream>
using namespace std;

PARABOLA_NAMESPACE_BEGIN

/// Creates a named scene graph 
SceneGraph::SceneGraph(const String &name) : Node(name){
	//myNodeType = SceneGraphNodeType::SceneGraph;
};
/*
/// Re-implementation of attachNode to avoid attaching invalid node types.
Node* SceneGraph::attachNode(Node* node){
	return Node::attachNode(node);
};
/// Updates the entire graph state by elapsedTime seconds
void SceneGraph::updateGraph(float elapsedTime){
	for(NodeIterator it = myChildren.begin(); it != myChildren.end(); it++){
		SceneLayer *l = dynamic_cast<SceneLayer*>(*it);
		if(l){
			l->updateGraph(elapsedTime);	
		}
	}
};

/// Creates a layer node
SceneLayer* SceneGraph::createLayer(const String &name){
	String fname = name;
	while(findLocalNodeByName(fname)){
		//the name already exists.
		fname = layerNameGenerator.generate();
	}
	SceneLayer* layer = new SceneLayer(fname);
	attachNode(layer);
	return layer;
};

/// Creates a new physics simulation
KinesisWorld* SceneGraph::createKinesisWorld(const String &name){
	KinesisWorld *world = new KinesisWorld();
	String fname = name;
	while(mySimulations.find(fname) != mySimulations.end()){
		// already exists
		fname = kinesisNameGenerator.generate();
	}
	
	SceneGraphSharedResource<KinesisWorld> resource;
	resource.owner = NULL;
	resource.resource = world;
	resource.locked = false;
	mySimulations[fname] = resource;

	return world;
};

/// Get the physics simulation
KinesisWorld* SceneGraph::getKinesisWorld(const String &name){
	if(mySimulations.find(name) != mySimulations.end()){
		return mySimulations[name].resource;
	}
	else return NULL;	
};

/// Meant to be called internally by SceneLayer, to request an asset
SceneGraphSharedResource<KinesisWorld>* SceneGraph::requestKinesisWorld(const String &name, SceneLayer* requestingLayer, bool requestOwnership){
	SimulationIterator it;
	if((it = mySimulations.find(name)) != mySimulations.end()){
		if(it->second.owner == NULL){
			// no owner, layer must own it
			it->second.owner = requestingLayer;			
		}
		else{
			// decide if it will get ownership
			if(requestOwnership && it->second.locked == false){
				it->second.owner = requestingLayer;	
			}
		}
		return &it->second;
	}
	else return NULL;
};

/// Destroys a physics simulation
void SceneGraph::destroyKinesisWorld(const String &name){
	if(mySimulations.find(name) != mySimulations.end()){
		mySimulations[name].owner = NULL;
		delete mySimulations[name].resource;
		mySimulations.erase(mySimulations.find(name));
	}
};

/// Renderer will call this.
void SceneGraph::render(SceneRenderer *renderer){
	for(NodeIterator it = myChildren.begin(); it != myChildren.end(); it++){
		SceneLayer *l = dynamic_cast<SceneLayer*>(*it);
		if(l){
			l->render(renderer);
		}
	}
};

/// Dispatch an event through the scene graph
bool SceneGraph::dispatchEvent(const Event &event){
	if(event.type == Event::MouseButtonPressed){
		cout<<"Got a mouse click."<<endl;
	}
	return false;
};
*/
PARABOLA_NAMESPACE_END
