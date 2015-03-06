#include <Nephilim/World/GameObject.h>

NEPHILIM_NS_BEGIN

/// Get the class RTTI for this game objectc class
FClass* GameObject::getClass()
{
	return _Class;
}

NEPHILIM_NS_END