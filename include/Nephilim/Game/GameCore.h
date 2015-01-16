#ifndef Nephillim_GameCore_h
#define Nephillim_GameCore_h

#include <Nephilim/Platform.h>
#include <Nephilim/VirtualFS.h>
#include <Nephilim/ContentManager.h>
#include <Nephilim/Clock.h>
#include <Nephilim/Logger.h>
#include <Nephilim/Graphics/GraphicsDevice.h>
#include <Nephilim/Event.h>
#include <Nephilim/StringList.h>

#include <Nephilim/Game/GameStateMachine.h>
#include <Nephilim/ContentManager.h>
#include <Nephilim/Localization.h>
#include <Nephilim/Audio/AudioManager.h>
#include <Nephilim/UI/UIManager.h>

#include <Nephilim/Game/BaseSceneManager.h>
#include <Nephilim/Game/GameInput.h>

#include <Nephilim/World/World.h>


NEPHILIM_NS_BEGIN

class Engine;
class Window;
class IScriptEngine;

/**
	\ingroup Core
	\class GameCore
	\brief Base class for all games and applications.

	This class contains all the necessary tools to build 
	a game as you inherit from it.

	You don't need to use all of its power, and you can take different
	solutions, but in 99% cases this class should be enough for most
	purposes.
	
*/
class NEPHILIM_API GameCore
{
public:

	/// The game instance can have N parallel realms
	std::vector<World*> gameWorlds;

	std::vector<IScriptEngine*> scriptEngines;

	/// The state manager, knows whats currently activated from the different game screens, and controls transitions nicely as well
	GameStateMachine stateManager;

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

	/// The central game input manager, used to query at any time for key state etc
	GameInput gameInput;


public: 
// Interface API

	/// Called before the game initializes, to set some properties
	/// For example, useful to allow or disallow automatic plugin loading
	/// or boot script running or not. Useful to cancel out some default behaviors the game does
	virtual void onPreSetup();
	
public:

	/// Construct the game, its mandatory to call this base constructor when implementing GameCore
	GameCore();
	
	/// Create a new scene or return if already exists
	World* createWorld(const String& name);

	/// Get the main world of this game
	/// If there are no spawned worlds, one will be created, otherwise the world 0 is always the main one
	World* getWorld();

	/// Create a new UICanvas for the game to use
	UICanvas* createCanvas(const String& name);

	/// Indexes all plugins found in /Plugins
	void loadPlugins();

	/// Get a pointer to the engine
	Engine* getEngine();

	/// Get the window/screen handler
	/// Returns nullptr when the game is windowless
	Window* getWindow();

	/// Shutdown this game immediately
	void close();

	/// Set the fixed update step, or, the amount of time, in seconds, that will take between each update.
	void setUpdateStep(float step);

	/// Get the game window title
	String getWindowTitle();

	/// Set the title of the window while the game is active
	void setWindowTitle(const String &title);

	/// Sets the base directory to load resources from
	void setFileRoot(const String & path);

	/// Set the name of the game
	void setName(const String& name);

	/// Get the name of the game
	String getName();
	
	/// Get the root for file loading on this game
	String getFileSystemRoot();

	GraphicsDevice* getRenderer();

	Engine* m_creator;

	/// Get the opengl version of this surface's context
	String getGLVersionString();

	/// Get the opengl renderer device name
	String getGLRendererString();

	/// Get the opengl vendor string
	String getGLVendorString();

	/// Get the flags of the gl context
	String getGLContextFlags();

	VirtualFS mVirtualFS;

protected:

	/// Callback for updating the game
	virtual void onUpdate(Time time);

	/// Callback for rendering a frame
	virtual void onRender();

	/// This function is called when a game is starting
	/// It is imperative that after running this function the game is on its first instant of execution, ready to progress with events and updates
	virtual void onCreate(); 

	/// Callback when an event happens
	virtual void onEvent(const Event &event);

	/// Can only use relative path resources from this directory
	/// The only alternative otherwise is to use absolute paths - which may be blocked in sandbox modes
	/// Either empty, an absolute path ending in a / or a relative path ending in a /
	String m_fileSystemRoot;

	/// Just a symbolic game name
	String m_gameName;

private:
	friend class Engine;
	/// Inner update of the game
	/// Will handle fixed update steps
	/// Callbacks to onUpdate(Time time) when appropriate
	void innerUpdate(Time time);

	/// Inner render of the game
	/// Callbacks to onRender()
	void innerRender();

	/// Fixed update step
	float m_updateStep;
	float m_stackedTime;

	/// The title of the window when this game is active
	String m_windowTitle;



	bool mCloseRequested;

// Private managing Methods
private:
	
	/// This will initialize the game effectively and then call onCreate()
	void PrimaryCreate();

	/// This will handle the OS event and deliver it down the game structures
	void PrimaryEventHandling(const Event& event);
};

NEPHILIM_NS_END
#endif // Nephillim_GameCore_h