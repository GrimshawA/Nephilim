#ifndef MINIMAL_BUILD
#include "Nephilim/EntityComponentFactory.h"

NEPHILIM_NS_BEGIN

/// Spawns a registered component without parameters
EntityComponent* EntityComponentFactory::spawnComponent(const String &componentName, Entity *parent){
	StringID id = makeStringID(componentName, false);

	ComponentInstancersIterator it = myComponentInstancers.find(id);

	if(it != myComponentInstancers.end()){
		return (EntityComponent*)it->second->instance();
	}
	else
		return NULL;
};

/// Spawns a registered component with a parameter list.
EntityComponent* EntityComponentFactory::spawnComponent(const String &componentName, const StringList &params, Entity *parent){
	return NULL;
};

NEPHILIM_NS_END
#endif