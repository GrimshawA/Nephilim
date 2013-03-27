#ifndef ForgeWorldNode_h__
#define ForgeWorldNode_h__

#include "Platform.h"
#include "Transformable.h"
#include "Renderer.h"

PARABOLA_NAMESPACE_BEGIN

/**
	\ingroup Forge
	\class ForgeWorldNode
	\brief All objects that are placed in a ForgeWorld, that can possibly be moved, scaled and rotated.
*/
class PARABOLA_API ForgeWorldNode : public Transformable{
public:

	virtual void draw(Renderer* renderer)=0;

	/// Unique id of the node
	Int64 m_uid;
};

PARABOLA_NAMESPACE_END
#endif // ForgeObject_h__
