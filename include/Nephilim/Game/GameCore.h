#ifndef Nephillim_GameCore_h
#define Nephillim_GameCore_h

#include <Nephilim/Platform.h>

#include <Nephilim/Foundation/VirtualFileSystem.h>
#include <Nephilim/Foundation/Clock.h>
#include <Nephilim/Foundation/Logging.h>
#include <Nephilim/Foundation/Event.h>
#include <Nephilim/Foundation/StringList.h>
#include <Nephilim/Foundation/Localization.h>

#include <Nephilim/Game/GameContent.h>
#include <Nephilim/Game/GameStateMachine.h>
#include <Nephilim/Game/GameMessage.h>
#include <Nephilim/Game/GameWorlds.h>
#include <Nephilim/Game/GameInput.h>
#include <Nephilim/Game/GameServer.h>
#include <Nephilim/Game/GameAudio.h> 
#include <Nephilim/Game/GameNetwork.h> 
#include <Nephilim/Game/GameExtensions.h> 

#include <Nephilim/Graphics/GraphicsDevice.h>

#include <Nephilim/UI/UIManager.h>

#include <Nephilim/World/World.h>

#include <memory>

NEPHILIM_NS_BEGIN

class Engine;
class Window;
class ExtensionScripting;
class ExtensionAudio;

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

	/// This game's server to sync remote clients and itself
	std::unique_ptr<GameServer> gameServer;

	/// List of currently setup scripting solutions
	std::vector<ExtensionScripting*> scriptingEnvironments;

	/// Hub for dealing with audio on this game
	GameAudio gameAudio;

	/// Hub for dealing with all the extensions in the game
	GameExtensions gameExtensions;

	/// Hub for dealing with networking on this game
	GameNetwork gameNetwork;

	/// The game instance can have N parallel realms
	std::vector<World*> gameWorlds;

	/// The state manager, knows whats currently activated from the different game screens, and controls transitions nicely as well
	GameStateMachine stateManager;

	/// The game is prepared to own an arbitrary number of scenes, stored in this object
	GameWorlds sceneManager;

	/// The game is always prepared to handle N individual user interface systems
	UIManager userInterfaceManager;

	/// The game can hold multiple resource groups and ensures their deallocation when closing
	GameContent contentManager;

	/// The game has multi language support natively, its lightweight and avoids boilerplate code
	LocalizationManager languageManager;

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

	/// Get the world by its name
	World* getWorld(const String& name);

	/// Render a given world
	void renderWorld(World* world);

	/// Returns whether this game is running as a server-only (no graphics)
	bool isDedicatedServer();

	/// Finds a registered scripting environment or returns nullptr
	ExtensionScripting* getScriptingEnvironment(const String& name);

	/// Finds a registered audio environment to play sounds with or returns nullptr
	ExtensionAudio* getAudioEnvironment(const String& name);

	/// Create a new UICanvas for the game to use
	UICanvas* createCanvas(const String& name);

	/// Get a UI canvas 
	UICanvas* getCanvas(const String& name);

	/// Indexes all plugins found in /Plugins
	void loadPlugins();

	/// Broadcast a message to every script
	void broadcastMessage(const GameMessage &gameMessage);

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

	VirtualFileSystem mVirtualFS;

protected:

	/// Callback for updating the game
	virtual void onUpdate(Time time);

	/// Callback for rendering a frame
	virtual void onRender();

	/// This function is called when a game is starting
	/// It is imperative that after running this function the game is on its first instant of execution, ready to progress with events and updates
	virtual void onCreate(); 

	/// Callback when an event happens
	virtual void onEvent(const Event& event);

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

	/// Internal update handling
	void PrimaryUpdate(Time time);
};

NEPHILIM_NS_END
#endif // Nephillim_GameCore_h