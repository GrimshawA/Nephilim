#ifndef PARABOLA_SCENELAYER_H
#define PARABOLA_SCENELAYER_H

#include "Platform.h"
#include "Node.h"
#include "EntityManager.h"

PARABOLA_NAMESPACE_BEGIN
class SceneGraph;
class SceneNode;
class SceneRenderer;
class KinesisWorld;
template<class T>
class SceneGraphSharedResource;
/**
	\ingroup SceneGraph
	\class SceneLayer
	\brief Represents a graphical subdivision of the scene.

	SceneLayer is perhaps the most important node in the scene, it manages everything in a layer.

	Some resources it manages can be shared, like a KinesisWorld, etc. 
	A layer can only reference one of this objects at a time, but the objects may be referenced by multiple layers.

	The layer which creates the resource, becomes its owner, and therefore reserves priority on using it.
*/
class PARABOLA_API SceneLayer : public Node{
public:

	/// Updates the entire graph state by elapsedTime seconds
	void updateGraph(float elapsedTime);

	/// Creates a new child scene node
	SceneNode* createSceneNode(const String &name);

	/// Creates a new entity manager
	EntityManager* getEntityManager();

	/// Assigns itself a previously created simulation
	bool useKinesisWorld(const String &name, bool requestOwnership);

	/// Returns the associated physics world, or NULL if none exists
	KinesisWorld* getKinesisWorld();
	

protected:
	/// Re-implementation of attachNode to avoid attaching invalid node types.
	virtual Node* attachNode(Node* node);

	/// Renders the layer
	virtual void render(SceneRenderer* renderer);

private:
	friend class SceneGraph;

	/// Reference to the entity manager, NULL by default
	std::unique_ptr<EntityManager> myEntityManager;

	/// Creates the named scene layer - only the SceneGraph must instance these.
	SceneLayer(const String &name);

	// Resources
	SceneGraphSharedResource<KinesisWorld>* mySimulation;
};

PARABOLA_NAMESPACE_END
#endif