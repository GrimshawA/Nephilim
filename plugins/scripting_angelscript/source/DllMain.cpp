// For the nephilim plugin interface
#include <Nephilim/Plugins/PluginSDK.h>

// For the actual plugin implementation
#include "ScriptingEnvironment_AS.h"

extern "C"
{
	__declspec(dllexport) ScriptingEnvironment *createScriptingEnvironment(GameCore* game)
	{
		return new ScriptingEnvironment_AS(game);
	}

	__declspec(dllexport) PluginSDK::Types getPluginType()
	{
		return PluginSDK::Scripting;
	}
}
