#ifndef NephilimEntityContainer_h__
#define NephilimEntityContainer_h__

#include <Nephilim/Platform.h>

NEPHILIM_NS_BEGIN

/**
	\class EntityContainer
	\brief This class is a pure virtual interface for any kind of entity container

	For flexibility, Nephilim supports changing the entity container and/or entity data.

	This could be useful for things like making more efficient entity storage or
	changing what data the entity can carry. However, for the crushing majority
	of cases, the default EntityContainer specialization in the engine should be
	enough.

*/
class NEPHILIM_API EntityContainer
{
public:

};

NEPHILIM_NS_END
#endif // NephilimEntityContainer_h__
