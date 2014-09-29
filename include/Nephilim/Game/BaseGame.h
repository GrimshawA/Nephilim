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
#include <Nephilim/Razer/Scene.h>

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
	StateStack stateManager;

	/// The game is prepared to own an arbitrary number of scenes, stored in this object
	BaseSceneManager sceneManager;

	/// The game is always prepared to handle N individual user interface systems
	UIManager userInterfaceManager;

	/// The game can hold multiple resource groups and ensures their deallocation when closing
	ContentManager contentManager;

	/// The game has multi language support natively, its lightweight and avoids boilerplate code
	LocalizationManager languageManager;

	/// The game has audio playback support built in, along with sound groups managing
	AudioManager audioManager;

	/// The game is prepared to be connected with 0 to many languages at once and they can all coexist in harmony
	std::vector<BaseScriptInterface*> scriptEngines;


public:
	BaseGame();

	/// Create a new scene or return if already exists
	rzr::Scene* createScene(const String& name);

};

NEPHILIM_NS_END
#endif // NephilimBaseGame_h__
