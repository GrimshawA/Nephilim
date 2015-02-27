#ifndef NephilimAsset_h__
#define NephilimAsset_h__

#include <Nephilim/Platform.h>

NEPHILIM_NS_BEGIN

/**
	\class Asset
	\brief All assets loaded on runtime are Asset derived objects

	This base class provides a common interface for all assets, so they can be inspected and type casted
	correctly, as well as reference counted in a uniform way.
*/
class NEPHILIM_API Asset
{
public:

};

NEPHILIM_NS_END
#endif // NephilimAsset_h__
