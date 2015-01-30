#ifndef NephilimRazerComponent_h__
#define NephilimRazerComponent_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Foundation/Object.h>

NEPHILIM_NS_BEGIN

/**
	\class Component
	\brief Represents one feature that can be added to a game object

	Inherits Object for later implementing RTTI databases around the Object
	inherited classes.
*/
class NEPHILIM_API Component : public Object
{
public:

	/// Destructor
	virtual ~Component();
};

NEPHILIM_NS_END
#endif // NephilimRazerComponent_h__
