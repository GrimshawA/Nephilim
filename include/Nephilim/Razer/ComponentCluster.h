#ifndef NephilimRazerComponentCluster_h__
#define NephilimRazerComponentCluster_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Razer/ComponentManager.h>

#include <vector>
#include <map>

NEPHILIM_NS_BEGIN
namespace rzr {

/**
	\class ComponentArray
	\brief Array of components, acting as a cache efficient pool of components of one type
*/
template<typename T>
class ComponentCluster : public ComponentManager
{
public:

};

};
NEPHILIM_NS_END
#endif // NephilimRazerComponentCluster_h__
