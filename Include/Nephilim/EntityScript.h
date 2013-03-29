#ifndef PARABOLA_ENTITYSCRIPT_H
#define PARABOLA_ENTITYSCRIPT_H

#include "Platform.h"
#include "Entity.h"

NEPHILIM_NS_BEGIN

class ASEngine;
class EntityManager;
/**
	\ingroup Scripting
	\ingroup SceneGraph
	\class EntityScript
	\brief A special entity that interacts with scripts, while having all the default functionality.
*/
class NEPHILIM_API EntityScript : public Entity{
public:
	/// Called when the entity is attached
	virtual void onAttach();

private:
	friend class EntityManager;
	/// Creates the entity script
	EntityScript(EntityManager *parent);

	ASEngine *myScriptEngine;
};

NEPHILIM_NS_END
#endif