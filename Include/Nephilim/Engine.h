/*
Copyright (C) 2010-2013 Artur Moreira - ParabolaEngine under zlib license

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

#ifndef PARABOLA_ENGINE_H
#define PARABOLA_ENGINE_H

#include "Platform.h"
#include "Clock.h"
#include "Strings.h"
#include "Surface.h"

PARABOLA_NAMESPACE_BEGIN
class GameCore;
class Renderer;
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
class PARABOLA_API Engine
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

	/// Get the current renderer
	Renderer* getRenderer();

private:
	GameCore*	m_currentApp;		///< The currently executing game/application
	Clock		m_clock;			///< Clock that counts the elapsed time since the engine was instanced
	Clock		m_stepClock;		///< Clock that merely counts the time between updates
	Renderer*	m_renderer;			///< The unified graphics renderer system
	Surface		m_surface;			///< The surface this engine is bound to
};

PARABOLA_NAMESPACE_END
#endif
