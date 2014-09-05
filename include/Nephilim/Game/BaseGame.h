#ifndef NephilimBaseGame_h__
#define NephilimBaseGame_h__

#include <Nephilim/Platform.h>
#include <Nephilim/GameCore.h>
#include <Nephilim/StateStack.h>

#include <Nephilim/Game/BaseSceneManager.h>

#include <memory>

NEPHILIM_NS_BEGIN

class BaseScriptInterface;

/**
	\class BaseGame
	\brief The base class from which every game is made

	While GameCore is the raw interface that encapsulates a single game instance
	in a multi-game engine, BaseGame is the ready-to-use game with all the features of 
	the engine inside.

	You can simply instance a BaseGame object in C++ and fully script it to make any game,
	without any C++ code. Also, you can avoid scripting, and simply extend BaseGame to meet your 
	needs using C++. Using both is also an ideal approach.

	You should use _always_ BaseGame to make your games with Nephilim. 
	Only roll your own if you are sure of what you are doing or there is a strong reason
	not to use BaseGame.
*/
class NEPHILIM_API BaseGame : public GameCore
{
public:

	/// The state manager, knows whats currently activated from the different game screens, and controls transitions nicely as well
	StateStack stateStack;

	/// The game is prepared to own an arbitrary number of scenes, stored in this object
	std::unique_ptr<BaseSceneManager> sceneManager;

	/// The game is prepared to be connected with 0 to many languages at once and they can all coexist in harmony
	std::vector<BaseScriptInterface*> scriptEngines;
};

NEPHILIM_NS_END
#endif // NephilimBaseGame_h__
