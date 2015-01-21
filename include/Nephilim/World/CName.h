#ifndef NephilimRazerComponentName_h__
#define NephilimRazerComponentName_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Foundation/String.h>
#include <Nephilim/World/Component.h>

NEPHILIM_NS_BEGIN
namespace rzr {

/**
	\class CName
	\brief Assigns a string to the entity
*/
class NEPHILIM_API CName : public Component
{
public:
	String name;
};
};
NEPHILIM_NS_END
#endif // NephilimRazerComponentName_h__
