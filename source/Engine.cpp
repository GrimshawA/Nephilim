#include <Nephilim/Engine.h>
#include <Nephilim/Game/GameCore.h>
#include <Nephilim/Graphics/GraphicsDevice.h>
#include <Nephilim/CGL.h>
#include <Nephilim/View.h>

#ifdef NEPHILIM_ANDROID
#include <Nephilim/AndroidInterface.h>
#endif

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
, m_window(nullptr)
{
};

Engine::~Engine()
{
	delete m_renderer;
};

/// Get a basic string describing the current OS
String Engine::getOS()
{
#ifdef NEPHILIM_WINDOWS
	return "Windows";
#elif defined NEPHILIM_ANDROID
	return "Android";
#else
	return "Other";
#endif
}

void Engine::execute(GameCore* app)
{
	m_currentApp = app;

	if(m_currentApp)
	{
		m_currentApp->m_creator = this;
		m_currentApp->PrimaryCreate();
	}
}

void Engine::init()
{

	// stub code
	m_window = new Window();
	m_window->create();

	cglPrepareExtensions();

	// Attempt to initialize the renderer
	m_renderer = m_window->createRenderer();

	m_running = m_renderer ? true : false;
}

void Engine::update()
{
	if(!m_running) return;

	// Check for removal first
	if(m_currentApp && m_currentApp->mCloseRequested)
	{
		m_currentApp = NULL;
		m_running = false;

		// In android need to kill the activity
#ifdef NEPHILIM_ANDROID
		AndroidInterface::closeActivity();
#endif
	}

	if(m_currentApp)
	{
		// Poll events
		Event event;
		while(m_window->pollEvent(event))
		{
			m_currentApp->PrimaryEventHandling(event);
		}

		while(!m_events.empty())
		{
			m_currentApp->PrimaryEventHandling(m_events[0]);
			m_events.erase(m_events.begin());
		}


		// Perform the update
		m_currentApp->innerUpdate(m_stepClock.getElapsedTime());
		m_stepClock.reset();

		// Draw a frame
		if(m_renderer)
		{
			render();			
		}
	}
};

/// Render one frame to the associated surface
void Engine::render()
{
	m_currentApp->innerRender();
	m_window->pushFrame();
}

/// Inject an event into the engine "pipeline"
void Engine::injectEvent(Event& event)
{
	m_events.push_back(event);
}

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
GraphicsDevice* Engine::getGraphicsDevice()
{
	return m_renderer;
}

/// Sets the command line arguments
void Engine::setArgs(int count, char** args)
{
	mArgumentCount = count;
	mArguments = args;
}

/// Returns a string with the version of the engine build. Usually like x.y.z
String Engine::getVersionString()
{
	return m_versionString;
}

NEPHILIM_NS_END

