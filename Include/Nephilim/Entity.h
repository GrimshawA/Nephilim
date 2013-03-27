#ifndef PARABOLA_ENTITY_H
#define PARABOLA_ENTITY_H

#include "Platform.h"
#include "Strings.h"
#include "SceneItem.h"
#include "EntityComponent.h"
#include "Vectors.h"
#include "StringID.h"
#include <map>
#include <vector>

PARABOLA_NAMESPACE_BEGIN

class SceneRenderer;
class EntityManager;
/**
	\ingroup SceneGraph
	\class Entity
	\brief A component-based entity

	...

*/
class PARABOLA_API Entity : public SceneItem{
public:
	/// Entity constructor, should not be instanced manually.
	Entity(EntityManager *parent);

	/// Adds a component to the entity, from the component factory
	virtual void addComponent(const String &componentName);

	/// Adds a component to the entity, from the component, and passes some initialization parameters
	virtual void addComponent(const String &componentName, const StringList &params);

	/// Called when the entity is attached
	/// Calls onAttach on its components as well, in most cases, there are none yet.
	virtual void onAttach();

	/// Called when the scene item is supposed to render
	virtual void onRender(SceneRenderer* renderer);

	/// Get the entity position
	/// Entities can have different positions than the parent scene node, because they may be simulated by physics
	Vec2f getPosition();

	/// Resets the entity position to the parent scene node
	void resetPosition();
	
protected:
	/// Attaching a component to the entity
	virtual void attachComponent(EntityComponent* component);

	/// List of all components that currently define this entity
	std::map<StringID, EntityComponent*> myComponents;
	typedef std::map<StringID, EntityComponent*>::iterator ComponentIterator;
	std::vector<EntityComponent*> myRenderComponents;

private:
	friend class EntityManager;	
	// Parent
	EntityManager *myEntityManager;

	Vec2f myPosition;
};
PARABOLA_NAMESPACE_END
#endif