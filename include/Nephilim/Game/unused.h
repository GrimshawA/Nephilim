#ifndef NephilimBaseGame_h__
#define NephilimBaseGame_h__

#include <Nephilim/Platform.h>
#include <Nephilim/GameCore.h>
#include <Nephilim/StateStack.h>
#include <Nephilim/ContentManager.h>
#include <Nephilim/Localization.h>
#include <Nephilim/Audio/AudioManager.h>
#include <Nephilim/UI/UIManager.h>

#include <Nephilim/Game/BaseSceneManager.h>
#include <Nephilim/Razer/World.h>

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
	
	


public:
	BaseGame();

	/// Create a new scene or return if already exists
	World* createScene(const String& name);

};

NEPHILIM_NS_END
#endif // NephilimBaseGame_h__
