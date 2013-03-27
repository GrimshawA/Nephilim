#ifndef PARABOLA_SCENENODE_H
#define PARABOLA_SCENENODE_H

#include "Platform.h"
#include "Node.h"
#include "Vectors.h"

#include <SFML/Graphics/Transform.hpp>

PARABOLA_NAMESPACE_BEGIN

class SceneGraph;
class SceneItem;
class SceneLayer;
class SceneRenderer;
/**
	\ingroup SceneGraph
	\class SceneNode
	\brief Represents a transformable node within the tree

	...
*/
class PARABOLA_API SceneNode : public Node{
public:
	/// Creates a scene node
	SceneNode();

	/// Creates a default named Scene Node
	SceneNode(const String &name);

	/// Attaches an item to this node, such as an entity, a camera, etc
	bool attachItem(SceneItem *item);

	/// Sets the position of this node, adjusting its children as well
	void setPosition(float x, float y);

	/// Get global position of this node
	Vec2f getGlobalPosition();

	/// Get local position of this node
	Vec2f getLocalPosition();

	/// Creates a new child scene node
	SceneNode* createSceneNode(const String &name);

	/// Get the layer this node is inserted into
	SceneLayer* getLayerNode();

	/// Updates the node and its children
	void update(float elapsedTime);

	/// Updates the node and its children
	void render(SceneRenderer *renderer);

	/// Debug
	void previewStructure(const String &data);

protected:
	typedef std::vector<SceneItem*>::iterator ItemIterator;

private:
	friend class SceneGraph;

	/// Child items
	std::vector<SceneItem*> myItems;

	Transform myTransform;
	Vec2f myLocalPosition;

	bool myUpdateState;
};

PARABOLA_NAMESPACE_END
#endif