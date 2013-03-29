#ifndef ForgeWorldNode_h__
#define ForgeWorldNode_h__

#include "Platform.h"
#include "Transformable.h"
#include "Renderer.h"

NEPHILIM_NS_BEGIN

/**
	\ingroup Forge
	\class ForgeWorldNode
	\brief All objects that are placed in a ForgeWorld, that can possibly be moved, scaled and rotated.
*/
class NEPHILIM_API ForgeWorldNode : public Transformable{
public:

	virtual void draw(Renderer* renderer)=0;

	/// Unique id of the node
	Int64 m_uid;
};

NEPHILIM_NS_END
#endif // ForgeObject_h__
