#ifndef NephilimWorldPlayerController_h__
#define NephilimWorldPlayerController_h__

#include <Nephilim/Platform.h>

NEPHILIM_NS_BEGIN

class World;
class Actor;

/**
	\class PlayerController
	\brief Recommended place to write player managing logic

	Inheriting or scripting this class is the recommended way to write player managing code.
	
	In order to program gameplay behaviors, aka, change the world state, we must write this logic somewhere.
	The options are to just do this in the gameplay state, searching and changing what is needed in the World instance.
	Another way is to write a system and process the World to do some kind of behavior (recommended in many cases).
	Finally, one can use Actors to react to input directly.

	However, the ideal way to do it is to use a PlayerController, which translates player logic into the World directly,
	making things react. For example, if in the game the character Actor dies a lot and is re-spawned in any way, it will be completely re instanced
	losing its data, so its better to have this data stored in the PlayerController, which is likely to be alive the entire game.

	Another advantage is that the player can easily swap between Actors and control them dynamically. For example, as long as every
	Actor is reacting to the Run action, the player can control one or many actors at once in any way.

	This is also useful to manage multiplayer, where users can hop-in dynamically.

	Finally, the editor will start communicating with the PlayerController when simulating the game. Usually in a joystick/keyboard only mode.
	This allows that the developer can actually edit the world with the mouse, while moving in it at the same time with the joystick.

	The editor can then have your own extended PlayerController and Actor subclasses by C++ factories, or script instanced extensions.

	This is also a nice place to control the active camera, so the editor can at any time disallow the camera code to use its own,
	and if needed activate the final game cameras, to behave as if we were in the actual game.

	PlayerController is also rigged to support networking naturally. Both in editor and in game. Basically,
	the client will be handling input and delivering it to its Actors. If a cracker patches the program so that the PlayerController
	delivers input to a different Actor instead (which doesn't belong to the player), this will simply be ignored by the server side,
	and that Actor will never move for other players.
*/
class NEPHILIM_API PlayerController
{
public:
	bool _mouseEnabled;     ///< Deliver the mouse input or not; in editor, its usually blocked completely
	bool _joystickEnabled;  ///< Deliver the joystick input or not
	bool _keyboardEnabled;  ///< Deliver the keyboard input or not

	World* _world;          ///< World this controller is attached to

public:

	/// Setup the active camera, the editor will not call this if it doesn't want to
	virtual void setupCamera();
};


/**
	\class PlayerControllerFactory
	\brief Factory to be registered in the World, to be instanced from name

	This is absolutely necessary for the editor to work with the game DLL.
	The editor will not know any game-specific classes, and will then spawn them by name,
	which is looked up in the factory list to spawn the actual classes.

	Unless the developer registers their classes in the scripting systems,
	they also will not know any C++ game classes. So, they can spawn things by name,
	using factories.
*/
template<typename T>
class NEPHILIM_API PlayerControllerFactory
{
public:
	T* instancePlayerController()
	{
		return new T();
	}
};

NEPHILIM_NS_END
#endif // NephilimWorldPlayerController_h__
