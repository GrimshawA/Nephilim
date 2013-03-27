#ifndef PARABOLA_SCRIPTGAME_H
#define PARABOLA_SCRIPTGAME_H

#include "Platform.h"
#include "GameCore.h"
#include "ASEngine.h"
#include "GameCoreInstancer.h"
#include "Sprite.h"
#include "Renderer.h"
#include "BrowserPreloader.h"
#include "StateStack.h"
#include "ContentBank.h"
#include "UIWindow.h"
#include "UIButton.h"
#include "UIManager.h"

#include <map>

PARABOLA_NAMESPACE_BEGIN


class MusicPlayer
{
public:

	void play(const String& name);
};

/**
	\ingroup Scripting
	\class ScriptGame
	\brief A pre-made game that can be completely controlled via scripting.

	Here you can read the basics on how to use this game, but there will be a wiki page dedicated to it.

	\todo under development. when done i remove this.
*/
class PARABOLA_API ScriptedGameCore : public GameCore{
public:
	ScriptedGameCore();

	/// Called when the game is instanced, calls int main() on the starter script
	void onCreate();

	/// Called when there is a new event
	void onEvent(Event &event);

	/// Called when the game needs to be updated
	void onUpdate(Time time);

	/// Draws the configured scene graph
	/// If the direct render script is enabled, it is rendered after the other objects.
	void onRender();

	/// Only called when the preload is finished so the game can start
	void startupGame();

	/// Sets the preload script. This is only useful before the onCreate() method
	void setPreloadScript(const String& script);

	/// Enable or disable the preload step, important in browsers to cache resources
	void enablePreloadStep(bool enable);

	/// Toggles the built-in console
	void toggleConsole();


	/// The state stack for the scripting
	StateStack m_states;

	/// AngelScript main engine
	ASEngine m_scripting;

	/// Content manager of the game
	ContentBank m_content;

	UIManager m_ui;

	MusicPlayer m_music;

	Window* m_window;

private:
	/// The path of the preload script
	String m_preloadScriptPath;
	/// The path of the main script
	String m_mainScriptPath;

	/// The preloader
	BrowserPreloader m_preloader;

	/// When in browsers, preload step is mandatory
	bool m_requiresPreload;


	ASScript* m_mainScript;

public:


	bool doDownload(String s, String d);

	sigc::signal<bool, String, String> onRequestDownload;

	String m_info;

	/// Exports all necessary functions to scripts
	void exportScripts();

	/// Set this name to be the one you want
	String entryPointScript;

	/// Render script
	String renderScriptName, renderScriptFunc;
	bool renderScriptEnabled;

	Texture m_texture;
	Sprite m_sprite;

	float circleX;

private:
	ASEngine m_engine;
	ASScript* m_script;

	Renderer *m_renderer;

	ASScript* myMainScript;
	int myRenderFunc, myEventFunc, myUpdateFunc, myCreateFunc;
	String m_startupScript;

	ASScript* m_preloadScript;
};

/**
	\ingroup Scripting
	\class ScriptGameInstancer
	\brief 
*/
class PARABOLA_API ScriptGameInstancer : public GameInstancerInterface{
public:	
	/// Prepares this instancer to create ScriptGame named as desired, and with entry point wherever wanted
	ScriptGameInstancer(String name, String entryPoint);

	/// Instances the ScriptGame
	GameCore* Instance();

private:
	String myName, myEntryPoint;
};

void registerScriptedGameCore(ASEngine* engine);

PARABOLA_NAMESPACE_END
#endif