#ifndef ASXModule_h__
#define ASXModule_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Strings.h>

class CScriptBuilder;
class asIScriptModule;

NEPHILIM_NS_BEGIN

class ASXEngine;

/**
	\ingroup Scripting
	\class ASXModule
	\brief Reference to a script module.

	Can be copied around without problems. 
	Beware, when requesting destruction of an ASXModule, all other references become invalid.
*/
class NEPHILIM_API ASXModule
{
public:
	ASXModule();

	ASXModule(asIScriptModule* module);

	asIScriptModule* get();

	operator bool();

private:
	asIScriptModule* m_module;
};

NEPHILIM_NS_END
#endif // ASXModule_h__
