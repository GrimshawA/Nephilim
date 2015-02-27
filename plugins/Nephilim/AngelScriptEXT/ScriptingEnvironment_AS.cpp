#include "ScriptingEnvironment_AS.h"
#include "ScriptSystem_AS.h"

ScriptSystem_AS* scriptSystem;

/// Prepare initial values
ScriptingEnvironment_AS::ScriptingEnvironment_AS(GameCore* game_parent)
{
	name = "angelscript";

	_game = game_parent;

	createScriptSystem();


	createGameBehavior("Scripts/Main.as");
}

/// Ensure the instance goes away safely
ScriptingEnvironment_AS::~ScriptingEnvironment_AS()
{

}

/// Make the scripting environment ready to start
void ScriptingEnvironment_AS::initialize()
{
	
}

/// Unload any loaded resources, back to an uninitialied state
void ScriptingEnvironment_AS::shutdown()
{

}

/// Update the game behaviors
void ScriptingEnvironment_AS::update(const Time& time)
{
	for (auto behavior : gameBehaviors)
	{
		behavior->call("void onUpdate()");
	}
}

/// Dispatch a GameMessage to all scripts
void ScriptingEnvironment_AS::dispatchToAll(const GameMessage& gameMessage)
{
	GameMessage m = gameMessage;

	//Log("DISPATCHING %s", m.temp.c_str());

	for (auto behavior : gameBehaviors)
	{
		//behavior->call("void OnMessage()");

		if (behavior->module->myModule)
		{
			/*ASXRuntime myRuntime(*behavior->_engine);

			ASXFunction func;
			func.mFunction = behavior->myModule.get()->GetFunctionByDecl(String("void OnMessage(GameMessage)").c_str());
			func.mRuntime = &myRuntime;
			func.prepare();
			func.mRuntime->get()->SetArgObject(0, &m);
			func.call();*/
		}
	}
}

/// Creates a new script system to pair up with a world
ScriptSystem* ScriptingEnvironment_AS::createScriptSystem()
{
	ScriptSystem_AS* ss = new ScriptSystem_AS(this);
	scriptSystem = ss;
	return ss;
}

/// This creates a scripting environment wide script
void ScriptingEnvironment_AS::createGameBehavior(const String& filename)
{
	ScriptBehavior* scriptBehavior = new ScriptBehavior();

	IScript* script = scriptSystem->compile(filename);

	script->call("void onCreate()");

	scriptBehavior->module = (ScriptModuleASX*)script;
	gameBehaviors.push_back(scriptBehavior);
}

void ScriptingEnvironment_AS::createStandaloneBehavior(const String& filename)
{

}
