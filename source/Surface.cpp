#include <Nephilim/Surface.h>
#include <Nephilim/Engine.h>
#include <Nephilim/CGL.h>
#include <Nephilim/RendererOpenGL.h>
#include <Nephilim/RendererGLES.h>
#include <Nephilim/RendererGLES2.h>

#if defined NEPHILIM_ANDROID
#include <Nephilim/AndroidInterface.h>
#endif

#ifdef NEPHILIM_WINDOWS
#include <windows.h>
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

/// Activate the surface as the active frame buffer
void Surface::activate()
{
	// this doesnt account ios yet
	glBindFramebufferCGL(GL_FRAMEBUFFER_CGL, 0); 
}

/// Set the title of the window if available
void Surface::setTitle(const String& title)
{
	window->setTitle(title);
}

/// Makes the window maximized - windows only
void Surface::maximize()
{
#ifdef NEPHILIM_WINDOWS
	HWND hnd = static_cast<HWND>(window->getHandle());
	ShowWindow(hnd, SW_SHOWMAXIMIZED);
#endif
}

/// Implements RenderTarget::getSize()
Vec2i Surface::getSize() const
{
	return Vec2i(static_cast<int>(getWidth()), static_cast<int>(getHeight()));
}

/// Change the size of the window if possible
void Surface::setSize(int width, int height)
{
	window->setSize(width, height);
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

	if(renderer)
	{
		renderer->m_target = this;
		renderer->m_surface = this;

		renderer->setDefaultTarget();
		renderer->setDefaultShader();
		renderer->setDefaultBlending();
		renderer->setDefaultTransforms();
		renderer->setDefaultViewport();
		renderer->setDefaultDepthTesting();
	}

	return renderer;
}

/// Convert a point in window-space to a homogeneous coordinate
vec2 Surface::convertToHomogeneousCoordinate(vec2i point)
{
	vec2 coords;
	coords.x = -1.f + 2.f * (point.x - 0) / getWidth();
	coords.y = 1.f  - 2.f * (point.y - 0)  / getHeight();
	return coords;
}

void Surface::create()
{
   // printf("Surface::create\n");
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

int Surface::getWidth() const
{
#if defined NEPHILIM_ANDROID || defined NEPHILIM_IOS
	return m_windowWidth;
#else
	return window->getWidth();
#endif
}
int Surface::getHeight() const
{
#if defined NEPHILIM_ANDROID || defined NEPHILIM_IOS
	return m_windowHeight;
#else
	return window->getHeight();
#endif
}

IntRect Surface::getViewport(const View& view) const
{
	float width  = static_cast<float>(getWidth());
	float height = static_cast<float>(getHeight());
	const FloatRect& viewport = view.getViewport();

	return IntRect(static_cast<int>(0.5f + width  * viewport.left),
		static_cast<int>(0.5f + height * viewport.top),
		static_cast<int>(width  * viewport.width),
		static_cast<int>(height * viewport.height));
}


NEPHILIM_NS_END
