#ifndef NephilimScriptSystem_h__
#define NephilimScriptSystem_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Foundation/String.h>
#include <Nephilim/World/System.h>
#include <Nephilim/Scripting/IScript.h>

NEPHILIM_NS_BEGIN

/**
	\class ScriptSystem
	\brief
*/
class NEPHILIM_API ScriptSystem : public System
{
public:
	virtual void testFunction() = 0;

	virtual IScript* compile(const String& filename){ return nullptr; }

	virtual void execute(const String& source){}

	virtual void registerFunction(const String& signature, void* funcPtr){}
};

NEPHILIM_NS_END

#endif // NephilimScriptSystem_h__
