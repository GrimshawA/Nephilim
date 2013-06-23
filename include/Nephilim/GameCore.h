#ifndef PARABOLA_GAMECORE_H
#define PARABOLA_GAMECORE_H

#include "Platform.h"
#include "Clock.h"
#include "Logger.h"
#include "Renderer.h"
#include "Window.h"
#include "Event.h"
#include "StringList.h"

NEPHILIM_NS_BEGIN
class GameCoreManager;
class Engine;
class Surface;
/**
	\ingroup Core
	\class GameCore
	\brief Base class for all games and applications.
	
*/
class NEPHILIM_API GameCore{
public:
	/// Construct the game, its mandatory to call this base constructor when implementing GameCore
	GameCore();

	/// Get a pointer to the engine
	Engine* getEngine();

	/// Get the window/screen handler
	Window& getWindow();

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

	Renderer* getRenderer();

	Surface& getSurface();

	Engine* m_creator;

	/// Get the opengl version of this surface's context
	String getGLVersionString();

	/// Get the opengl renderer device name
	String getGLRendererString();

	/// Get the opengl vendor string
	String getGLVendorString();

	/// Get the flags of the gl context
	String getGLContextFlags();

protected:

	/// Callback for updating the game
	virtual void onUpdate(Time time);

	/// Callback for rendering a frame
	virtual void onRender();

	/// This function is called when a game is starting
	/// It is imperative that after running this function the game is on its first instant of execution, ready to progress with events and updates
	virtual void onCreate(); 

	/// Callback when an event happens
	virtual void onEvent(Event &event);

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
};

NEPHILIM_NS_END
#endif