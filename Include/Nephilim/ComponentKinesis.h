#ifndef PARABOLA_ENTITYCOMPONENT_KINESISACTOR_H
#define PARABOLA_ENTITYCOMPONENT_KINESISACTOR_H

#include "Platform.h"
#include "EntityComponent.h"
#include "Vectors.h"

PARABOLA_NAMESPACE_BEGIN

/**
	\ingroup SceneGraph
	\class ComponentKinesisActor
	\brief Manipulates one or more physics bodies.


*/
class PARABOLA_API ComponentPhysicsCompound : public EntityComponent{
public:
	/// Creates the compound instance
	ComponentPhysicsCompound(const String &name);

	/// Called when the component is attached
	void onAttach();

	/// Make this compound a bridge (a few bodies, connected by joints)
	void createBridge(Vec2f bridgeStart, Vec2f bridgeEnd, int stepCount);

	/// Make this compound own a bridge
	void createRope(Vec2f ropeStart, float fraglen, int fragments);
};

PARABOLA_NAMESPACE_END
#endif