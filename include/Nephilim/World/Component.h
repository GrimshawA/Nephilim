#ifndef NephilimRazerComponent_h__
#define NephilimRazerComponent_h__

#include <Nephilim/Platform.h>
#include <Nephilim/World/CHandle.h>

NEPHILIM_NS_BEGIN

/**
	\class Component
	\brief Represents one characteristic added to entities

	It is recommended for each component to be 64 or less bytes,
	due to possible performance gains by benefiting from the CPU cache lines.
*/
class NEPHILIM_API Component
{
public:
};

NEPHILIM_NS_END
#endif // NephilimRazerComponent_h__
