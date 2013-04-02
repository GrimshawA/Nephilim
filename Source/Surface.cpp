#include <Nephilim/Surface.h>
#include <Nephilim/RendererOpenGL.h>
#include <Nephilim/RendererGLES.h>
#include <Nephilim/RendererGLES2.h>

#include <stdio.h>

NEPHILIM_NS_BEGIN

/// Construct the surface object - not yet valid
Surface::Surface()
: m_renderer(NULL)
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


NEPHILIM_NS_END
