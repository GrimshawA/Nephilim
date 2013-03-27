#ifndef PARABOLA_SCENEOBJECT_H
#define PARABOLA_SCENEOBJECT_H

#include "Platform.h"
#include "Strings.h"
#include <SFML/Graphics/Transform.hpp>

PARABOLA_NAMESPACE_BEGIN
class SceneRenderer;
class SceneNode;
/**
	\ingroup SceneGraph
	\class SceneItem
	\brief Represents objects that can attach to nodes for rendering, etc
*/
class PARABOLA_API SceneItem{
public:
	/// Creates the scene item
	SceneItem();

	/// Returns the name of the item
	String name();

	/// Called when the item is attached to a node
	virtual void onAttach();

	/// Called when the scene item is supposed to render
	virtual void onRender(SceneRenderer* renderer);

	/// Get the SceneNode that owns this item, directly or indirectly.
	virtual SceneNode* getParentSceneNode();

protected:
	/// Sets the name of the item
	void setName(const String &name);

private:
	friend class SceneNode;
	/// Item name, normally unique
	String myName;
	/// Scene node parent
	SceneNode* mySceneNodeParent;
};

PARABOLA_NAMESPACE_END
#endif