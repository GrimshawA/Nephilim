#include <ParabolaCore/Engine.h>
#include <ParabolaCore/GameCore.h>
#include <ParabolaCore/Renderer.h>

#include <ParabolaCore/View.h>

PARABOLA_NAMESPACE_BEGIN
	
Engine::Engine()
: m_currentApp(NULL)
, m_renderer(NULL)
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

	// Attempt to initialize the renderer
	m_renderer = Renderer::createAutomaticRenderer(m_surface.window);
}

void Engine::update()
{
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

/// Get the current renderer
Renderer* Engine::getRenderer()
{
	return m_renderer;
}

PARABOLA_NAMESPACE_END

