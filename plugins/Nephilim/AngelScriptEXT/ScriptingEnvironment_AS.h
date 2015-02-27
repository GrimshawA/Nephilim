#ifndef ScriptingEnvironment_AS_h__
#define ScriptingEnvironment_AS_h__

#include <Nephilim/Game/GameCore.h>
#include <Nephilim/Extensions/ExtensionScripting.h>
#include <Nephilim/World/Systems/ScriptSystem.h>
using namespace nx;

#include <Nephilim/AngelScriptEXT/ASXEngine.h>
#include <Nephilim/AngelScriptEXT/ScriptBehavior.h>

class ScriptModuleASX;

/*
	\class ScriptingEnvironment_AS
	\brief Coordinates the entire angel script integration with the engine

	# Every given behavior instance is an individual ScriptBehavior instance too, 1:1,
	be it a system, a prefab, state or anything.
*/
class ScriptingEnvironment_AS : public ExtensionScripting
{
public:

	ASXEngine engine;

	/// Cache of all scripts currently instanced and ready to use
	/// These can have multiple purposes in the engine, but are collected here for a safe destruction etc.
	std::vector<ScriptBehavior*> gameBehaviors;

public:

	/// Prepare initial values
	ScriptingEnvironment_AS(GameCore* game_parent);

	/// Ensure the instance goes away safely
	~ScriptingEnvironment_AS();

	/// Make the scripting environment ready to start
	void initialize();

	/// Unload any loaded resources, back to an uninitialied state
	void shutdown();

	/// Update the game behaviors
	virtual void update(const Time& time);

	/// Creates a new script system to pair up with a world
	ScriptSystem* createScriptSystem();

	/// This creates a scripting environment wide script
	virtual void createGameBehavior(const String& filename);

	void createStandaloneBehavior(const String& filename);

	/// Dispatch a GameMessage to all scripts
	virtual void dispatchToAll(const GameMessage& gameMessage);

};


#endif // ScriptingEnvironment_AS_h__
