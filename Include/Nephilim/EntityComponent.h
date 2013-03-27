#ifndef PARABOLA_ENTITYCOMPONENT_H
#define PARABOLA_ENTITYCOMPONENT_H

#include "Platform.h"
#include "Strings.h"

PARABOLA_NAMESPACE_BEGIN

class Entity;
/**
	\ingroup SceneGraph
	\class EntityComponent
	\brief Base class for all components

	All components must inherit from EntityComponent, implementing the appropriate methods.

	For optimizing performance, components work in a registration fashion.
	If your component needs to render, it should register as a drawable.
	If your component needs to update something, it should register appropriately.

	If that doesn't provide enough information for your components to update their state,
	you can exchange messages between them, and act accordingly.

	Some components, such as an AI decision-maker, may not need to be updated every frame,
	appropriate efficient tools will be made to optimize this. \todo AI

*/
class PARABOLA_API EntityComponent{
public:
	/// Creates an empty component - abstract
	EntityComponent(const String &name);

	/// Destructor
	virtual ~EntityComponent();

	/// Called when the component is activated by an entity
	virtual void onAttach() = 0;

	/// Get the component name - the name registered in the factory
	String getName();

	/// Get the parent entity, NULL if the component is not attached yet
	Entity* getParentEntity();

private:
	/// Is this component shared or unique/configurable?!
	bool myShared;
	/// All components must have a unique name.
	String myName;
	/// Components that are not shared may have different configurations,
	/// therefore a user may want to name each one differently.
	String myUserName;
	/// Parent Entity
	Entity* myParent;
	friend class Entity;
};

PARABOLA_NAMESPACE_END
#endif