#ifndef NephilimScriptingEnvironment_h__
#define NephilimScriptingEnvironment_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Strings.h>

NEPHILIM_NS_BEGIN

class IScript;

/**
	\class ScriptingEnvironment
	\brief Interface for integrating a scripting language

	The engine has one instance of ScriptingEnvironment per
	scripting language and interfaces with it to give scripting support 
	to the game.
*/
class NEPHILIM_API ScriptingEnvironment
{
public:
	virtual void testFunction() = 0;

	virtual IScript* compile(const String& filename){ return nullptr; }

	virtual void execute(const String& source){}

	virtual void registerFunction(const String& signature, void* funcPtr){}
};

NEPHILIM_NS_END
#endif // NephilimScriptingEnvironment_h__
