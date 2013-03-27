#ifndef PARABOLA_ENTITYSCRIPT_H
#define PARABOLA_ENTITYSCRIPT_H

#include "Platform.h"
#include "Entity.h"

PARABOLA_NAMESPACE_BEGIN

class ASEngine;
class EntityManager;
/**
	\ingroup Scripting
	\ingroup SceneGraph
	\class EntityScript
	\brief A special entity that interacts with scripts, while having all the default functionality.
*/
class PARABOLA_API EntityScript : public Entity{
public:
	/// Called when the entity is attached
	virtual void onAttach();

private:
	friend class EntityManager;
	/// Creates the entity script
	EntityScript(EntityManager *parent);

	ASEngine *myScriptEngine;
};

PARABOLA_NAMESPACE_END
#endif