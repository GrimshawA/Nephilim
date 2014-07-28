#ifndef NephilimScriptEntity_h__
#define NephilimScriptEntity_h__

#include <Nephilim/Platform.h>

NEPHILIM_NS_BEGIN
namespace rzr{
/**
	\class ScriptEntity
	\brief Base class for script language accessible entities

	ScriptEntity acts as the base class for multiple "entity" or "gameobject" implementations as 
	visible from script languages. They act merely as wrappers around the genuine native Entity
	contained in a Scene, exposing functionality directly to the scripting language.
	
	For example, if we were to use Lua, Mono and AngelScript, we could have one ScriptEntity
	implementation for each of the languages, to make sure everything is done in the most appropriate
	way for the given scripting language.
*/
class NEPHILIM_API ScriptEntity
{
public:

};

};
NEPHILIM_NS_END
#endif // NephilimScriptEntity_h__
