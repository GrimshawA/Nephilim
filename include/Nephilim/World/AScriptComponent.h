#ifndef NephilimWorldAScriptComponent_h__
#define NephilimWorldAScriptComponent_h__

#include <Nephilim/Platform.h>
#include <Nephilim/World/Component.h>


NEPHILIM_NS_BEGIN

class IScript;

/**
	\class AScriptComponent
	\brief Allows to attach a scripted behavior to the actor

	These behaviors are used to program gameplay logic into actors.
	The actors are configured usually in a prefab and then spawned into the
	world, as the engine handles all this natively. Then, one can give behavior to the actor
	simply by adding a behavior to it.

	Behaviors can be pretty generic or very problem specific, but they usually
	focus on the more high-level logic of the game. For example, we can make an
	enemy actor be spawned in the world many times, and they just idle around until
	a script is added to give them behavior. The script may then give each enemy
	the ability to move and manage all animations autonomously, move with pathfinding and so on,
	follow the player etc.

	This is really powerful as it gives life to the game world and not only makes
	characters, vehicles and other assets interesting, but it also helps writing the game
	rules.

	One actor/entity can have multiple scripts in it, but the only way to script a game object
	is through this component.
*/
class AScriptComponent : public Component
{
public:
	/// Whether the behavior is enabled
	bool enabled = true;

	IScript* _script = nullptr;

	/// This object represents the individual instance of the behavior for this component
	void* object = nullptr;

	/// Tick the script
	void tickScript();
};

NEPHILIM_NS_END
#endif // NephilimWorldAScriptComponent_h__
