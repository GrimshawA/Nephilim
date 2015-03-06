#ifndef NephilimWorldComponentText_h__
#define NephilimWorldComponentText_h__

#include <Nephilim/Platform.h>
#include <Nephilim/World/ASceneComponent.h>
#include <Nephilim/Foundation/String.h>

NEPHILIM_NS_BEGIN

/**
	\class ATextComponent
	\brief Ability to render text inside the game world
*/
class NEPHILIM_API ATextComponent : public ASceneComponent
{
public:

	/// The text string
	String text;
};

NEPHILIM_NS_END
#endif // NephilimWorldComponentText_h__