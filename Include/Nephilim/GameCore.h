#ifndef PARABOLA_GAMECORE_H
#define PARABOLA_GAMECORE_H

#include "Platform.h"
#include "Clock.h"
#include "Logger.h"
#include "Renderer.h"
#include "Window.h"
#include "Event.h"
#include "StringList.h"
#include "Application.h"

PARABOLA_NAMESPACE_BEGIN
class GameCoreManager;
class Engine;
/**
	\ingroup Core
	\class GameCore
	\brief Base class for all games and applications.
	
*/
class PARABOLA_API GameCore{
public:
	/// Construct the game, its mandatory to call this base constructor when implementing GameCore
	GameCore();

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

	Engine* m_creator;

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
	friend class GameCoreManager;
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

	
	/*
	/// Get the assigned window
	/// Returns a NULL smart pointer if no window exists
	Window* getWindow();

	/// Sets the primary window
	/// It is mandatory that a window is set for onRender to be called.
	void setWindow(Window* window);

	/// Get the name of this game
	String& name();

	/// Get the current window title
	/// By default, it says "Default Game Name"
	String& windowTitle();

	/// Set the window title
	void setWindowTitle(const String &title);
	
	/// Destroys this game at the end of the update
	void close();

	/// Runs a script command
	void runScript(const String &command);

	/// Get a reference to the script engine
	ScriptEngine& scriptEngine();


	/// Creates a renderer pointing at the render target passed in
	/// If the target is NULL, it tries to bind the renderer to the current window
	SceneRenderer* createRenderer(RenderTarget *target);
	
	/// Creates a sound player or returns if already exists
	/// If a sound player with that name already exists,
	/// it is returned instead of creating a new one
	SoundPlayer& getSoundPlayer(const String &name);

	/// Destroys a sound player
	void removeSoundPlayer(const String &name);

	/// Get a content bank 
	/// If the selected content bank doesn't exist, it is created.
	ContentBank& getContentBank(const String &name);

	/// Destroy a content bank
	void removeContentBank(const String &name);

protected:
	/// Callback when the game was just instanced
	virtual void onCreate();

	/// Callback when the game is about to be destroyed
	virtual void onDestroy();

	/// Callback when the game enters the execution list
	virtual void onUpdateFocus();

	/// Callback when the game is removed from the execution list
	virtual void onUpdateLostFocus();

	/// Callback when the game becomes the active drawing game
	virtual void onRenderFocus();

	/// Callback when the game can't render anymore
	virtual void onRenderLostFocus();

	/// Callback to draw on the window
	virtual void onRender();

	/// Callback to handle the event
	virtual void onEvent(const Event &event);

	/// Callback to update the game state by elapsedTime seconds
	virtual void onUpdate(float elapsedTime);

	/// Protected constructor, cannot instance GameCore
	GameCore();
	
private:
	friend class GameCoreManager;
	GameCoreManager *myParent;

	/// Inner Create is responsible to proper initialize the game if the constructor is not called
	void innerCreate();

	/// Inner update is responsible to call the regular onUpdate
	/// Also handles fixed time step
	void innerUpdate(Uint32 elapsedTime);

	/// Inner render will check if there is an associated window, and only in that case it will draw into it
	/// Calls SetActive() on the window, clears the buffer and displays it.
	void innerRender();

	/// Inner Event Check takes the associated window and gets events from it
	void innerEventCheck();

	/// Inner Activate will do the intern preparations for the game to be drawing
	void innerActivate();

	/// Inner Deactivate will do the preparations for the game to stop drawing
	void innerDeactivate();

	/// Fixed time step - 0 for no fixed time step
	float fixedUpdateStep, accumulatedTime;
	/// Window title, will be automatically activated
	String myWindowTitle;
	/// Name of the game instance
	String myName;
	/// Screen clearing color
	Color clearColor;
	/// Localization Settings
	String mySystemLocale, mySelectedLocale;
	/// Current drawing window
	/// If there is an engine window, it is assigned here by default
	Window* myWindow;
	/// True if this game is allowed to render
	bool activeDrawing;
	/// Each game owns a intern script engine
	ScriptEngine myScriptEngine;

	/// Sound Players
	std::map<String, SoundPlayer*> mySoundPlayers;

	/// Content banks
	std::map<String, ContentBank*> myContentBanks;

	/// Scripting interface functions - all defined in AngelScriptInterfaces.cpp
	friend class ASEngine;

	void dummy();*/
};

PARABOLA_NAMESPACE_END
#endif