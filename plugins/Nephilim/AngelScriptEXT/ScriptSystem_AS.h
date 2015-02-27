#ifndef CorePluginScriptEngineASX_h__
#define CorePluginScriptEngineASX_h__

#include <Nephilim/World/Systems/ScriptSystem.h>

#include <Nephilim/Scripting/IScript.h>
using namespace nx;

#include <Nephilim/AngelScriptEXT/ASXEngine.h>
#include <Nephilim/AngelScriptEXT/ASXFunction.h>
#include <Nephilim/AngelScriptEXT/ASXRuntime.h>
#include <Nephilim/AngelScriptEXT/ASXModuleBuilder.h>

class ScriptingEnvironment_AS;

class ScriptSystem_AS : public ScriptSystem
{
public:

	ScriptingEnvironment_AS* _env = nullptr;

public:

	/// Prepare the scripting system to function with Nephilim
	ScriptSystem_AS(ScriptingEnvironment_AS* env);

	void registerFunction(const String& signature, void* funcPtr);

	void testFunction();

	IScript* compile(const String& filename);

	void execute(const String& source);
};

class ScriptModuleASX : public IScript
{
public:
	ASXModule myModule;
	ASXEngine* _engine;
public:

	void call(const String& funcName);

	virtual void callOnObject(const String& func, void* obj);

	virtual void* createClassInstance(const String& className);

	virtual void setMemberRef(const String& identifier, void* obj, void* ref);
};

#endif // CorePluginScriptEngineASX_h__
