#ifndef NephilimAngelScriptEXT_ScriptBehavior_h__
#define NephilimAngelScriptEXT_ScriptBehavior_h__

#include <Nephilim/Foundation/String.h>
using namespace nx;

#include <angelscript.h>

class ScriptModuleASX;

/**
	\class ScriptBehavior
	\brief Every instanced behavior in the angel script plugin lives as a ScriptBehavior

	A script behavior can actually share the same class and module with another,
	being just different objects.
*/
class ScriptBehavior
{
public:
	ScriptModuleASX* module;

	/// The instance object of this behavior
	asIScriptObject* object = nullptr;

public:
	/// Constructor
	ScriptBehavior();

	/// Call a function on this behavior
	void call(const String& func);
};

#endif // NephilimAngelScriptEXT_ScriptBehavior_h__
