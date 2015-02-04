#ifndef ScriptingEnvironment_AS_h__
#define ScriptingEnvironment_AS_h__

#include <Nephilim/Game/GameCore.h>
#include <Nephilim/Scripting/ScriptingEnvironment.h>
#include <Nephilim/World/ScriptSystem.h>
using namespace nx;

/// Angelscript wrappers
#include <Nephilim/ASX/ASXEngine.h>

class ScriptModuleASX;

/*
	\class ScriptingEnvironment_AS
	\brief Coordinates the entire angel script integration with the engine
*/
class ScriptingEnvironment_AS : public ScriptingEnvironment
{
public:

	ASXEngine engine;

	/// Cache of all scripts currently instanced and ready to use
	/// These can have multiple purposes in the engine, but are collected here for a safe destruction etc.
	std::vector<ScriptModuleASX*> gameBehaviors;

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

	/// Dispatch a GameMessage to all scripts
	virtual void dispatchToAll(const GameMessage& gameMessage);

};


#endif // ScriptingEnvironment_AS_h__
