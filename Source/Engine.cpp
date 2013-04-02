#include <Nephilim/Engine.h>
#include <Nephilim/GameCore.h>
#include <Nephilim/Renderer.h>
#include <Nephilim/CGL.h>
#include <Nephilim/View.h>

NEPHILIM_NS_BEGIN

#ifdef ENGINE_VERSION_STRING
	String Engine::m_versionString = /*ENGINE_VERSION_STRING*/ "fixme";
#else
	String Engine::m_versionString = "unknown";
#endif

Engine::Engine()
: m_currentApp(NULL)
, m_renderer(NULL)
, m_running(false)
{

};

Engine::~Engine()
{
	delete m_renderer;
};

void Engine::execute(GameCore* app)
{
	m_currentApp = app;

	if(m_currentApp)
	{
		m_currentApp->m_creator = this;
		m_currentApp->onCreate();
	}
}

void Engine::init()
{

	// stub code
	m_surface.create();

	cglPrepareExtensions();

	// Attempt to initialize the renderer
	m_renderer = m_surface.createRenderer();

	m_running = m_renderer ? true : false;
}

void Engine::update()
{
	if(!m_running) return;

	// Check for removal first
	if(m_currentApp && m_currentApp->mCloseRequested)
	{
		m_currentApp = NULL;
	}

	if(m_currentApp)
	{
		// Poll events
		Event event;
		while(m_surface.window->pollEvent(event))
		{
			m_currentApp->onEvent(event);
		}


		// Perform the update
		m_currentApp->innerUpdate(m_stepClock.getElapsedTime());
		m_stepClock.reset();

		// Draw a frame
		if(m_renderer)
		{
			View mView;
			mView.setRect(0,0, m_surface.window->getWidth(), m_surface.window->getHeight());
			m_renderer->pushView(mView);
			m_renderer->clear();
			m_currentApp->innerRender();
			m_renderer->display();
			m_surface.window->swapBuffers();
		}
	}
};

/// Terminate the engine completely
void Engine::shutdown()
{

}

/// Returns true if the engine was initialized and has a valid surface and renderer
bool Engine::isRunning()
{
	return m_running;
}

/// Get the current renderer
Renderer* Engine::getRenderer()
{
	return m_renderer;
}

/// Sets the command line arguments
void Engine::setArgs(int count, char** args)
{

}

/// Returns a string with the version of the engine build. Usually like x.y.z
String Engine::getVersionString()
{
	return m_versionString;
}

NEPHILIM_NS_END

