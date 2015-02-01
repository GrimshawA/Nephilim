#ifndef NephilimExtensionScripting_h__
#define NephilimExtensionScripting_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Foundation/Extension.h>
#include <Nephilim/Foundation/String.h>
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
class NEPHILIM_API ExtensionScripting : public Extension
{
public:

	/// All scripting environments have a name to be retrieved easily
	String name;

	/// This is the game the scripting environment is linked to
	GameCore* _game;

public:

	/// Ensure safe destruction
	virtual ~ExtensionScripting();

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
#endif // NephilimExtensionScripting_h__
