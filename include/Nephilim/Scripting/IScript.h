#ifndef NephilimIScript_h__
#define NephilimIScript_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Strings.h>

NEPHILIM_NS_BEGIN

/**
	\class IScript
	\brief Interface to call functions on scripts
*/
class NEPHILIM_API IScript
{
public:
	virtual	void call(const String& funcName){}
};

NEPHILIM_NS_END

#endif // NephilimIScript_h__
