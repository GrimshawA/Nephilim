#ifndef NephilimBaseState_h__
#define NephilimBaseState_h__

#include <Nephilim/Platform.h>
#include <Nephilim/State.h>

NEPHILIM_NS_BEGIN

/**
	\class BaseState
	\brief A fully featured state with scripting capabilities

	Its base class, State, is simply the bare bones of any state,
	all it does is to have the minimal interface to work together
	with the state stack mechanism and therefore allow self contained screens
	in each State.

	BaseState is for State what BaseGame is for GameCore;
	A specialization of a really basic interface to give it a lot
	more feature.

	So, naturally, one should always inherit from BaseState,
	so the script engine can access it and manipulate it easily.

	Part of the Game/ submodule, as its a really high level
	feature of the engine.
*/
class NEPHILIM_API BaseState : public State
{
public:

	/// Simplest way to call a function in all the attached scripts
	/// No error handling or checking
	void callScriptFunction(const String& name);

	/// Check how many scripts are attached to this state
	std::size_t getNumAttachedScripts();
};

NEPHILIM_NS_END
#endif // NephilimBaseState_h__
