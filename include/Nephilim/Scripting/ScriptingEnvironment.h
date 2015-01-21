#ifndef NephilimScriptingEnvironment_h__
#define NephilimScriptingEnvironment_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Strings.h>
#include <Nephilim/Foundation/Time.h>
#include <Nephilim/Game/GameMessage.h>

NEPHILIM_NS_BEGIN

class GameCore;
class IScript;
class ScriptSystem;

/**
	\class ScriptingEnvironment
	\brief Interface for integrating a scripting language

	The engine has one instance of ScriptingEnvironment per
	scripting language and interfaces with it to give scripting support 
	to the game.
*/
class NEPHILIM_API ScriptingEnvironment
{
public:

	/// All scripting environments have a name to be retrieved easily
	String name;

	/// This is the game the scripting environment is linked to
	GameCore* _game;

public:

	/// Ensure safe destruction
	virtual ~ScriptingEnvironment();

	/// Creates a new script system to pair up with a game world
	virtual ScriptSystem* createScriptSystem(){ return nullptr; }

	/// This creates a scripting environment wide script
	virtual void createGameBehavior(const String& filename){}

	/// Update the game behaviors
	virtual void update(const Time& time){}

	/// Dispatch a GameMessage to all scripts
	virtual void dispatchToAll(const GameMessage& gameMessage){}
};

NEPHILIM_NS_END
#endif // NephilimScriptingEnvironment_h__
