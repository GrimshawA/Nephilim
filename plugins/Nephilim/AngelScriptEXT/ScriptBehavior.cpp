#include <Nephilim/AngelScriptEXT/ScriptBehavior.h>
#include <Nephilim/AngelScriptEXT/ScriptSystem_AS.h>

/// Constructor
ScriptBehavior::ScriptBehavior()
{

}

/// Call a function on this behavior
void ScriptBehavior::call(const String& func)
{
	module->call(func);
}

