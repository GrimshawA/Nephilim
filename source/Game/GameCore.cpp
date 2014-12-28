#include <Nephilim/Game/GameCore.h>
#include <Nephilim/Engine.h>
#include <Nephilim/CGL.h>
#include <Nephilim/StringList.h>
#include <Nephilim/FileSystem.h>
#include <Nephilim/Logger.h>

NEPHILIM_NS_BEGIN

/// Construct the game, its mandatory to call this base constructor when implementing GameCore
GameCore::GameCore()
: m_stackedTime(0.f)
, m_updateStep(1.f / 60.f)
, m_windowTitle("No name window")
, mCloseRequested(false)
{
	stateManager.mGame = this;
}

/// Called before the game initializes, to set some properties
/// For example, useful to allow or disallow automatic plugin loading
/// or boot script running or not. Useful to cancel out some default behaviors the game does
void GameCore::onPreSetup()
{

}

/// Indexes all plugins found in /Plugins
void GameCore::loadPlugins()
{
	StringList dll_list = FileSystem::scanDirectory("Plugins", "dll", false);
	for (auto& dll_name : dll_list)
	{
		Log("Plugin: %s", dll_name.c_str());
	}
}

/// Create a new scene or return if already exists
World* GameCore::createWorld(const String& name)
{
	World* world = sceneManager.createScene(name);

	// Init this world
	world->graphicsDevice = getRenderer();
	world->contentManager = &contentManager;

	return world;
}

/// Get the main world of this game
/// If there are no spawned worlds, one will be created, otherwise the world 0 is always the main one
World* GameCore::getWorld()
{
	if (sceneManager.mScenes.empty())
	{
		return createWorld("main");
	}
	else
	{
		return sceneManager.mScenes[0];
	}
}

/// Create a new UICanvas for the game to use
UICanvas* GameCore::createCanvas(const String& name)
{
	return userInterfaceManager.createCanvas(name);
}

/// Get a pointer to the engine
Engine* GameCore::getEngine()
{
	return m_creator;
}

/// Get the window/screen handler
Window* GameCore::getWindow()
{
    return m_creator->m_window;
}

/// Sets the base directory to load resources from
void GameCore::setFileRoot(const String & path)
{
	m_fileSystemRoot = path;
}

/// Get the root for file loading on this game
String GameCore::getFileSystemRoot()
{
	return m_fileSystemRoot;
}

GraphicsDevice* GameCore::getRenderer()
{
	return m_creator->getGraphicsDevice();
}

/// Get the opengl version of this surface's context
String GameCore::getGLVersionString()
{
	const GLubyte* str = glGetString(GL_VERSION);
	return reinterpret_cast<const char*>(str);
}

/// Get the opengl renderer device name
String GameCore::getGLRendererString()
{
	const GLubyte* str = glGetString(GL_RENDERER);
	return reinterpret_cast<const char*>(str);
}

/// Get the opengl vendor string
String GameCore::getGLVendorString()
{
	const GLubyte* str = glGetString(GL_VENDOR);
	return reinterpret_cast<const char*>(str);
}

/// Get the flags of the gl context
String GameCore::getGLContextFlags()
{
	//const GLubyte* str = glGetString(GL_VENDOR);
	//return reinterpret_cast<const char*>(str);
	return "";
}

/// Shutdown this game immediately
void GameCore::close(){
	mCloseRequested = true;
};

/// Set the name of the game
void GameCore::setName(const String& name)
{
	m_gameName = name;
};

/// Get the name of the game
String GameCore::getName()
{
	return m_gameName;
};

/// Set the fixed update step, or, the amount of time, in seconds, that will take between each update.
void GameCore::setUpdateStep(float step){
	m_updateStep = step;
};

/// Callback for updating the game
void GameCore::onUpdate(Time time){}

/// Callback for rendering a frame
void GameCore::onRender(){}

/// Callback when starting to execute the game
void GameCore::onCreate(){}

/// Callback when an event happens
void GameCore::onEvent(const Event &event){}

/// Get the game window title
String GameCore::getWindowTitle()
{
	return m_windowTitle;
}

/// Set the title of the window while the game is active
void GameCore::setWindowTitle(const String &title){
	m_windowTitle = title;
};

/// Inner update of the game
/// Will handle fixed update steps
/// Callbacks to onUpdate(Time time) when appropriate
void GameCore::innerUpdate(Time time)
{
	// Frame skipping when too much time is accumulated
	while(m_stackedTime > 0.5f)
	{
		m_stackedTime -= 0.5f;
	}

	m_stackedTime += time.asSeconds();
	while(m_stackedTime >= m_updateStep)
	{
		onUpdate(Time::fromSeconds(m_updateStep));
		m_stackedTime -= m_updateStep;
	}
}

/// Inner render of the game
/// Callbacks to onRender()
void GameCore::innerRender()
{
	onRender();
}

////////////////////////////////////////////////////////////////////////// INTERNAL

/// This will initialize the game effectively and then call onCreate()
void GameCore::PrimaryCreate()
{
	// Plugins are ready when the game starts to construct
	loadPlugins();

	onCreate();
}

/// This will handle the OS event and deliver it down the game structures
void GameCore::PrimaryEventHandling(const Event& event)
{

	onEvent(event);
}

NEPHILIM_NS_END
