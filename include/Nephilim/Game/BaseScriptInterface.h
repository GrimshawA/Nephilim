#ifndef NephilimBaseScriptInterface_h__
#define NephilimBaseScriptInterface_h__

#include <Nephilim/Platform.h>

NEPHILIM_NS_BEGIN

/**
	\class BaseScriptInterface
	\brief Base class for scripting engines

	This class is the base class for different scripting engines.
	In order to implement support for a new language in the engine,
	one must inherit BaseScriptInterface, so that language can coexist
	in a BaseGame instance or BaseGame inherited instance.

	Each different language will usually inherit this class,
	so there could be for example a ScriptInterfaceCSharp,
	a ScriptInterfaceAngelScript and a ScriptInterfaceLua;

	Each of them would hook to the same BaseGame instance and
	therefore that BaseGame, its states, resources and other properties
	could be manipulated from the scripting language in multiple ways.
*/
class NEPHILIM_API BaseScriptInterface
{
public:

};

NEPHILIM_NS_END
#endif // NephilimBaseScriptInterface_h__
