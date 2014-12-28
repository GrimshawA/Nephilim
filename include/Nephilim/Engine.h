/*
Copyright (C) 2010-2013 Artur Moreira - Nephilim under zlib license

This software is provided 'as-is', without any express or implied
warranty.  In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/
#ifndef NephilimEngine_h__
#define NephilimEngine_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Clock.h>
#include <Nephilim/Strings.h>
#include <Nephilim/Event.h>
#include <Nephilim/Window.h>

#include <vector>
#include <memory>

NEPHILIM_NS_BEGIN

class GameCore;
class GraphicsDevice;

/**
	\ingroup Core
	\class Engine
	\brief The main game engine controller

	Surface:
		As long as the engine is initialized it is bound to a valid surface. This is a golden rule that must always apply.
		Whenever the surface goes invalid for either reason, the engine has to pause or halt and cannot continue execution.
		Examples of surfaces: Browser's HTML Element's Frame, Windows in most common desktop systems, the Android/iOS device's screen

	GameCore:
		One game or application that can be run by the engine.

	Renderer:
		A unified interface for rendering graphics in a cross-platform way provided to the GameCore instances

	@author Artur Moreira
*/
class NEPHILIM_API Engine
{
public:
	/// Constructs the engine and leaves it in a uninitialized state
	Engine();

	/// Destructs the engine and waits for its proper internal destruction first
	~Engine();

	/// Executes the game immediately
	void execute(GameCore* app);

	/// Initializes the engine. This function either creates a surface or binds to an already existing one
	void init();

	/// Fetch input, update state and draw frame if appropriate
	void update();

	/// Render one frame to the associated surface
	void render();

	/// Terminate the engine completely
	void shutdown();

	/// Returns true if the engine was initialized and has a valid surface and renderer
	bool isRunning();

	/// Sets the command line arguments
	void setArgs(int count, char** args);

	/// Inject an event into the engine "pipeline"
	void injectEvent(Event& event);

	/// Get the current renderer
	GraphicsDevice* getGraphicsDevice();

	/// Get a basic string describing the current OS
	String getOS();

	/// Returns a string with the version of the engine build. Usually like x.y.z
    static String getVersionString();

	int glesHint;

public:
	GameCore*	m_currentApp;		///< The currently executing game/application
	Clock		m_clock;			///< Clock that counts the elapsed time since the engine was instanced
	Clock		m_stepClock;		///< Clock that merely counts the time between updates
	GraphicsDevice*	m_renderer;		///< The unified graphics renderer system
	Window*     m_window;
	bool		m_running;			///< Qualified as running if some conditions are met
	static String m_versionString;  ///< The version of string(at compile time)
	std::vector<Event> m_events;    ///< The list of unprocessed events
	int         mArgumentCount;
	char**      mArguments;
};

NEPHILIM_NS_END
#endif // NephilimEngine_h__
