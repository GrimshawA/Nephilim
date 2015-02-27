// For the nephilim plugin interface
#include <Nephilim/Extensions/PluginSDK.h>

// For the actual plugin implementation
#include <Nephilim/AngelScriptEXT/ScriptingEnvironment_AS.h>

extern "C"
{
	__declspec(dllexport) ExtensionScripting *createScriptingEnvironment(GameCore* game)
	{
		return new ScriptingEnvironment_AS(game);
	}

	__declspec(dllexport) PluginSDK::Types getPluginType()
	{
		return PluginSDK::Scripting;
	}
}
