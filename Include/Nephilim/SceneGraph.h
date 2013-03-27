#ifndef PARABOLA_SCENEGRAPH_H
#define PARABOLA_SCENEGRAPH_H

#include "Platform.h"
#include "Node.h"
/*
#include "SceneLayer.h"
#include "NameGenerator.h"
#include "EntityManager.h"
#include "SceneNode.h"
#include "Events.h"

#include <vector>
#include <map>
*/
/**
	\defgroup SceneGraph
	High-level module to manage game logic and rendering.
*/

PARABOLA_NAMESPACE_BEGIN
class SceneRenderer;
class KinesisWorld;
/*
template<class T>
class PARABOLA_API SceneGraphSharedResource{
public:
	T *resource;
	SceneLayer *owner;
	bool locked;
};
*/
/**
	\ingroup SceneGraph
	\class SceneGraph
	\brief Represents a Scene Graph, a structure that can hold ALL the game logic.

	...
*/
class PARABOLA_API SceneGraph : public Node{
public:
	/// Creates a named scene graph
	SceneGraph(const String &name);

	/// Updates the entire graph state by elapsedTime seconds
	/*void updateGraph(float elapsedTime);

	/// Dispatch an event through the scene graph
	/// Returns whether or not the event was used.
	bool dispatchEvent(const Event &event);

	/// Creates a layer node
	/// If you specify a name that already exists, it will be overwritten by an automatic name.
	SceneLayer* createLayer(const String &name);

	/// Creates a new physics simulation
	KinesisWorld* createKinesisWorld(const String &name);

	/// Get the physics simulation
	KinesisWorld* getKinesisWorld(const String &name);

	/// Destroys a physics simulation
	void destroyKinesisWorld(const String &name);

protected:
	/// Re-implementation of attachNode to avoid attaching invalid node types.
	virtual Node* attachNode(Node* node);

	/// Renderer will call this.
	void render(SceneRenderer *renderer);

	/// Meant to be called internally by SceneLayer, to request an asset
	SceneGraphSharedResource<KinesisWorld>* requestKinesisWorld(const String &name, SceneLayer* requestingLayer, bool requestOwnership);

private:
	friend class SceneRenderer;
	friend class SceneLayer;

	/// The physics
	std::map<String, SceneGraphSharedResource<KinesisWorld> > mySimulations;
	typedef std::map<String, SceneGraphSharedResource<KinesisWorld> >::iterator SimulationIterator;

	NameGenerator layerNameGenerator;
	NameGenerator kinesisNameGenerator;*/
};


PARABOLA_NAMESPACE_END
#endif