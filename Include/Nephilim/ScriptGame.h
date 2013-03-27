#ifndef PARABOLA_SCRIPTGAME_H
#define PARABOLA_SCRIPTGAME_H

#include "Platform.h"
#include "GameCore.h"
#include "ASEngine.h"
#include "GameCoreInstancer.h"
#include "Sprite.h"
#include "Renderer.h"

PARABOLA_NAMESPACE_BEGIN

/**
	\ingroup Scripting
	\class ScriptGame
	\brief A pre-made game that can be completely controlled via scripting.

	Here you can read the basics on how to use this game, but there will be a wiki page dedicated to it.



	\todo under development. when done i remove this.
*/
class PARABOLA_API ScriptGame : public GameCore{
public:
	/// Initializes the scripted game from a specific script
	ScriptGame(const String& startupScript = "GameMain.as");
	
	/// Called when the game is instanced, calls int main() on the starter script
	void onCreate();

	///Called when there is a new event
	void onEvent(Event &event);

	/// Called when the game needs to be updated
	void onUpdate(Time time);

	/// Draws the configured scene graph
	/// If the direct render script is enabled, it is rendered after the other objects.
	void onRender();

	/// Exports all necessary functions to scripts
	void exportScripts();

	/// Set this name to be the one you want
	String entryPointScript;

	/// Render script
	String renderScriptName, renderScriptFunc;
	bool renderScriptEnabled;

	Texture m_texture;
	Sprite m_sprite;
private:
	ASEngine m_engine;
	ASScript* m_script;

	Renderer *m_renderer;

	ASScript* myMainScript;
	int myRenderFunc, myEventFunc, myUpdateFunc, myCreateFunc;
	String m_startupScript;
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

PARABOLA_NAMESPACE_END
#endif