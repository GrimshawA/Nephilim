#ifndef NephilimExtensionScripting_h__
#define NephilimExtensionScripting_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Foundation/Extension.h>
#include <Nephilim/Foundation/String.h>
#include <Nephilim/Foundation/Time.h>
#include <Nephilim/Game/GameMessage.h>

#include <stdint.h>

NEPHILIM_NS_BEGIN

class GameCore;
class IScript;
class ScriptSystem;

namespace ScriptType
{
	enum ClassTypeFlags
	{
		ReferenceOnly = 0,  ///< These types are not instanceable from script, only from the native side
		RefCounted = 1
	};
};

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

	/// Registers a new type in the scripting plugin
	virtual void registerType(const String& name, std::size_t size, uint32_t classFlags);
};

NEPHILIM_NS_END
#endif // NephilimExtensionScripting_h__
