#ifndef PARABOLA_ENTITYMANAGER_H
#define PARABOLA_ENTITYMANAGER_H

#include "Platform.h"
#include "Entity.h"
#include "EntityScript.h"
#include "EntityComponentFactory.h"
#include "NameGenerator.h"
#include <list>

PARABOLA_NAMESPACE_BEGIN
class ASEngine;

/**
	\ingroup SceneGraph
	\class EntityManager
	\brief Holds all entities in a layer.
*/
class EntityManager{
public:
	/// Creates the empty entity manager
	EntityManager();

	/// Get the component factory
	EntityComponentFactory& getComponentFactory();

	/// Registers the default components into the component factory
	void registerDefaultComponents();

	Entity* createScriptedEntity(const String &name, ASEngine &scriptEngine);

	/// Creates an empty entity
	Entity* createEntity(const String &name);

private:
	/// For now, store them in a list.
	std::list<Entity*> myEntities;

	/// Component factory
	EntityComponentFactory myComponentFactory;

	NameGenerator entityNameGenerator;
};

PARABOLA_NAMESPACE_END
#endif