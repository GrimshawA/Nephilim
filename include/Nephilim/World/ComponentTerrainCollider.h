#ifndef NephilimRazerComponentTerrainCollider_h__
#define NephilimRazerComponentTerrainCollider_h__

#include <Nephilim/Platform.h>
#include <Nephilim/World/Component.h>

NEPHILIM_NS_BEGIN
namespace rzr
{

/**
	\class ComponentTerrainCollider
	\brief 
*/
class NEPHILIM_API ComponentTerrainCollider : public Component
{
public:
	ComponentTerrainCollider();

	bool ready;
};

};
NEPHILIM_NS_END
#endif // NephilimRazerComponentTerrainCollider_h__
