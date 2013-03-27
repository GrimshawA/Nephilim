#ifndef PARABOLA_ENTITYCOMPONENTMANAGER_H
#define PARABOLA_ENTITYCOMPONENTMANAGER_H

#include "Platform.h"
#include "StringID.h"
#include "StringList.h"
#include <vector>
#include <map>
#include "EntityComponent.h"

PARABOLA_NAMESPACE_BEGIN
class PARABOLA_API ComponentInstancer{
public:
	virtual void* instance(){return NULL;}
	virtual void* instance(const StringList &params){return NULL;}
protected:
	bool myShared;
	void* myObject;
	int myRefCount;
	String myComponentName;
};

template<class T>
class PARABOLA_API ComponentInstancerGeneric : public ComponentInstancer {
public:
	virtual void* instance(){
		EntityComponent* comp = new T(myComponentName);
		return comp;
	}
	virtual void* instance(const StringList &params){
		EntityComponent* comp = new T(myComponentName);
		return comp;
	}
};

/**
	\ingroup SceneGraph
	\class EntityComponentFactory
	\brief Manages the components used by entities.

	Works as a factory of components, so they can be easily found and added to an entity
*/
class PARABOLA_API EntityComponentFactory{
public:

	/// Spawns a registered component without parameters
	EntityComponent* spawnComponent(const String &componentName, Entity *parent);

	/// Spawns a registered component with a parameter list.
	EntityComponent* spawnComponent(const String &componentName, const StringList &params, Entity *parent);

	template<class T>
	void registerComponent(const String &name);

private:
	/// Structures capable of locating components and instancing them
	/// 
	std::map<StringID, ComponentInstancer*> myComponentInstancers;
	typedef std::map<StringID, ComponentInstancer*>::iterator ComponentInstancersIterator;
};

template<class T>
void EntityComponentFactory::registerComponent(const String &name){
	myComponentInstancers[makeStringID(name, false)] = new ComponentInstancerGeneric<T>();
};
PARABOLA_NAMESPACE_END
#endif