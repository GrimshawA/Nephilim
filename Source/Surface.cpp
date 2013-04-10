#include <Nephilim/Surface.h>
#include <Nephilim/Engine.h>
#include <Nephilim/RendererOpenGL.h>
#include <Nephilim/RendererGLES.h>
#include <Nephilim/RendererGLES2.h>

#if defined NEPHILIM_ANDROID
#include <Nephilim/AndroidInterface.h>
#endif

#include <stdio.h>

NEPHILIM_NS_BEGIN

/// Construct the surface object - not yet valid
Surface::Surface(Engine* engine)
: m_renderer(NULL)
, m_engine(engine)
{

}

/// Ensure proper destruction
Surface::~Surface()
{
	delete m_renderer;
}

/// Creates and returns the renderer if valid
Renderer* Surface::createRenderer()
{
	Renderer* renderer = NULL;

	// Try to assemble the renderer
	#ifdef NEPHILIM_DESKTOP
		renderer = new RendererOpenGL();

	#elif defined NEPHILIM_ANDROID || defined NEPHILIM_IOS
		if(m_engine->glesHint == 2)
			renderer = new RendererGLES2();
		else
			renderer = new RendererGLES();
	#endif

	if(renderer) renderer->m_renderTarget = window;

	return renderer;
}

void Surface::create()
{
    printf("Surface::create\n");
	window = new Window();
	window->create(1024,768);
};

/// Pushes the back buffer to the screen
void Surface::pushFrame()
{
	window->swapBuffers();
#if defined NEPHILIM_ANDROID
	AndroidInterface::requestFrameRender();
#endif
}


NEPHILIM_NS_END
