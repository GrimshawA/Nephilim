#ifndef NephilimIScriptEngine_h__
#define NephilimIScriptEngine_h__

#include <Nephilim/Platform.h>

NEPHILIM_NS_BEGIN

/**
	\class IScriptEngine
	\brief Base class for implementing scripting language support

	If you mean to implement your own language or third party one,
	start here.

	In order for the engine to communicate with each scripting engine we may throw at it, it needs an established interface,
	and this is it.

	Implementing this interface and throwing an instance of it at the engine and here it goes.

	This is how the engine tells the scripting engine to call functions,
	create objects and other kinds of utilities.

	It also makes it easy to add new languages at runtime, through plugins.
	Though, implementations can be compiled and instanced directly from core engine or core game if desired.
*/
class NEPHILIM_API IScriptEngine
{
public:
	virtual void testFunction() = 0;

};

NEPHILIM_NS_END

#endif // NephilimIScriptEngine_h__
