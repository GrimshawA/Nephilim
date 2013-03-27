#ifndef MINIMAL_BUILD
#include "Nephilim/EntityManager.h"
#include "Nephilim/ComponentKinesis.h"

PARABOLA_NAMESPACE_BEGIN

/// Creates the empty entity manager
EntityManager::EntityManager() : entityNameGenerator("entity"){
	registerDefaultComponents();
};

/// Registers the default components into the component factory
void EntityManager::registerDefaultComponents(){
	getComponentFactory().registerComponent<ComponentPhysicsCompound>("default::physicscompound");
};

/// Get the component factory
EntityComponentFactory& EntityManager::getComponentFactory(){
	return myComponentFactory;
};

Entity* EntityManager::createScriptedEntity(const String &name, ASEngine &scriptEngine){
	myEntities.push_back(new EntityScript(this));
	myEntities.back()->setName(name);
	((EntityScript*)myEntities.back())->myScriptEngine = &scriptEngine;
/*	myEntities.back()->onAttach(); this not here.*/

	return myEntities.back();
};


/// Creates an empty entity
Entity* EntityManager::createEntity(const String &name){
	myEntities.push_back(new Entity(this));
	myEntities.back()->setName(name);
	return myEntities.back();
};
PARABOLA_NAMESPACE_END
#endif