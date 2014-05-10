#ifndef NephilimRazerComponentName_h__
#define NephilimRazerComponentName_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Strings.h>
#include <Nephilim/Razer/Component.h>

NEPHILIM_NS_BEGIN
namespace rzr {

/**
	\class ComponentName
	\brief Assigns a string to the entity
*/
class NEPHILIM_API ComponentName : public Component
{
public:
	String name;
};
};
NEPHILIM_NS_END
#endif // NephilimRazerComponentName_h__
