#include <Nephilim/Window.h>
#include <Nephilim/Logger.h>

#include <Nephilim/Graphics/GL3/RendererOpenGL.h>
#include <Nephilim/Graphics/GLES/RendererGLES.h>
#include <Nephilim/Graphics/GLES2/RendererGLES2.h>
#include <Nephilim/CGL.h>

#ifdef NEPHILIM_DESKTOP
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#endif

#ifdef NEPHILIM_WINDOWS
#include <windows.h>
#endif

#include <iostream>
#include <stdint.h>
using namespace std;


NEPHILIM_NS_BEGIN

#ifdef NEPHILIM_DESKTOP
class Window::WindowImplementation : public sf::Window{
public:
	WindowImplementation() : sf::Window(){

	}
};
#else
class Window::WindowImplementation{
public:

};
#endif

/// Default constructor
Window::Window(){
	myWindowImpl = new WindowImplementation();
	m_fullscreen = false;
}

/// Destroy the window
Window::~Window(){
	delete myWindowImpl;
}

/// Move the window by an amount
void Window::move(int x, int y)
{
#ifdef NEPHILIM_WINDOWS
	HWND hnd = static_cast<HWND>(getHandle());
	MoveWindow(hnd, x, y, width(), height(), true);
#endif
}

/// Attempts to launch a window if applicable
void Window::create(int screenWidth, int screenHeight)
{
#ifdef NEPHILIM_DESKTOP
	myWindowImpl->create(sf::VideoMode(screenWidth,screenHeight), "Nephilim SDK", sf::Style::Default, sf::ContextSettings(32, 8 , 8));
	m_fullscreen = false;
	myWindowImpl->setVerticalSyncEnabled(true);
	//myWindowImpl->setFramerateLimit(60);
	
	static_cast<sf::Window*>(myWindowImpl)->onDragDrop.connect(sigc::mem_fun(this, &Window::handleInternalDragDrop));

	//Log("Window(%dx%dx%d - depth(%d) AA(%d) stencil(%d) ",myWindowImpl->getSize().x, myWindowImpl->getSize().y, 32, myWindowImpl->getSettings().depthBits, myWindowImpl->getSettings().antialiasingLevel, myWindowImpl->getSettings().stencilBits );
	//m_handle = (int)myWindowImpl->getSystemHandle();

#endif

};

/// Redirect drag and drop listener
void Window::handleInternalDragDrop(int x, int y, const StringList& fileNames)
{
	onDragDrop(x, y, fileNames);
}

/// Sets a new title to the window
void Window::setTitle(const String &title)
{

}

/// Activate the surface as the active frame buffer
void Window::activate()
{
	// this doesnt account ios yet
	glBindFramebufferCGL(GL_FRAMEBUFFER_CGL, 0);
}

/// Change the size of the window if possible
void Window::setSize(int width, int height)
{
#ifdef NEPHILIM_DESKTOP
	myWindowImpl->setSize(sf::Vector2u(width, height));
#endif
}

/// Makes the window maximized - windows only
void Window::maximize()
{
#ifdef NEPHILIM_WINDOWS
	HWND hnd = static_cast<HWND>(getHandle());
	ShowWindow(hnd, SW_SHOWMAXIMIZED);
#endif
}

void Window::create()
{
	create(1024, 768);
}

IntRect Window::getViewport(const View& view) const
{
	float w = static_cast<float>(width());
	float h = static_cast<float>(height());
	const FloatRect& viewport = view.getViewport();

	return IntRect(static_cast<int>(0.5f + w  * viewport.left),
		static_cast<int>(0.5f + h * viewport.top),
		static_cast<int>(w  * viewport.width),
		static_cast<int>(h * viewport.height));
}

/// Creates and returns the renderer if valid
GraphicsDevice* Window::createRenderer()
{
	GraphicsDevice* renderer = NULL;

	// Try to assemble the renderer
#ifdef NEPHILIM_DESKTOP
	renderer = new RendererOpenGL();

#elif defined NEPHILIM_ANDROID || defined NEPHILIM_IOS
	if (m_engine->glesHint == 2)
		renderer = new RendererGLES2();
	else
		renderer = new RendererGLES();
#endif

	if (renderer)
	{
	//	renderer->m_target = this;
		renderer->m_window = this;

		renderer->setDefaultTarget();
		renderer->setDefaultShader();
		renderer->setDefaultBlending();
		renderer->setDefaultTransforms();
		renderer->setDefaultViewport();
		renderer->setDefaultDepthTesting();
	}

	return renderer;
}

/// Pushes the back buffer to the screen
void Window::pushFrame()
{
	swapBuffers();
#if defined NEPHILIM_ANDROID
	AndroidInterface::requestFrameRender();
#endif
}


void Window::create(void* handle)
{
#ifdef NEPHILIM_DESKTOP
	myWindowImpl->create(reinterpret_cast<sf::WindowHandle>(handle));
	m_fullscreen = false;
	m_handle = reinterpret_cast<intptr_t>(handle);
#endif
};

/// Sets the window as active for drawing
bool Window::setActive(bool flag) const{
#ifdef NEPHILIM_DESKTOP
	return myWindowImpl->setActive(flag);
#endif
	return false;
};

void Window::setFramerateLimit(int limit){
#ifdef NEPHILIM_DESKTOP
	myWindowImpl->setFramerateLimit(limit);
#endif
};


/// Get the width of the screen/window
int Window::width() const
{
#if defined NEPHILIM_ANDROID || defined NEPHILIM_IOS
	return m_windowWidth;
#else
	return myWindowImpl->getSize().x;
#endif
};

/// Get the height of the screen/window
int Window::height() const
{
#if defined NEPHILIM_ANDROID || defined NEPHILIM_IOS
	return m_windowHeight;
#else
	return myWindowImpl->getSize().y;
#endif
};

/// Get the size of the window
Vec2i Window::getSize() const{
	return (Vec2i(width(), height()));
};

void Window::setMousePosition(Vec2i point)
{
#ifdef NEPHILIM_DESKTOP
	myWindowImpl->setMouseCursorVisible(false);
	sf::Mouse::setPosition(sf::Vector2i(point.x,point.y), *myWindowImpl);
#endif
}


/// Enable/Disable fullscreen mode
void Window::setFullscreen(bool enable){
#ifdef NEPHILIM_DESKTOP
	if(enable){
		//activate fullscreen
		myWindowImpl->create(sf::VideoMode::getDesktopMode(), "Hawkeye", sf::Style::Fullscreen);
	}
	else{
		myWindowImpl->create(sf::VideoMode(1024,768,32), "Hawkeye", sf::Style::Default);
	}

	m_fullscreen = enable;

#endif
};

/// Convert a point in window-space to a homogeneous coordinate
vec2 Window::convertToHomogeneousCoordinate(vec2i point)
{
	vec2 coords;
	coords.x = -1.f + 2.f * (point.x - 0) / width();
	coords.y = 1.f - 2.f * (point.y - 0) / height();
	return coords;
}


/// Convert a point from target coordinates to the view coordinates
Vec2f Window::convertCoords(const Vec2i &point, const View &view){
	// First, convert from viewport coordinates to homogeneous coordinates
	Vec2f coords;
	IntRect viewport = getViewport(view);
	coords.x = -1.f + 2.f * (point.x - viewport.left) / viewport.width;
	coords.y = 1.f  - 2.f * (point.y - viewport.top)  / viewport.height;

	// Then transform by the inverse of the view matrix
	return view.getInverseTransform().transformPoint(coords);
};

/// Get the fullscreen mode
bool Window::getFullscreen(){
	return m_fullscreen;
};

/// Check if there is a pending event
bool Window::pollEvent(Event &event){
#ifdef NEPHILIM_DESKTOP
	sf::Event tevent;
	if(myWindowImpl->pollEvent(tevent)){
		event.type = (Event::EventType)(int)tevent.type;
		event.mouseButton = *static_cast<Event::MouseButtonEvent*>((void*)&tevent.mouseButton);

		//event = static_cast<InputEvent>((void*)&tevent);
		//memcpy(&event, &tevent, sizeof(event.type)/* + sizeof(InputEvent::KeyEvent)*/);
	//	cout<<"Size of event::; "<<sizeof(tevent)<<endl;
		return true;
	}
	else return false;
#else
	return false;
#endif
};

/// Discard all pending events
void Window::discardEvents(){
#ifdef NEPHILIM_DESKTOP
	sf::Event event;
	while(myWindowImpl->pollEvent(event));
#endif
};

WindowHandle Window::getHandle()
{
#ifdef NEPHILIM_DESKTOP
	return (void*)myWindowImpl->getSystemHandle();
#endif
};

/// Swaps buffers
void Window::swapBuffers(){
#ifdef NEPHILIM_DESKTOP
	myWindowImpl->display();
#endif
};

//////////////////////////////////////////////////////////////////////////

/// Get the width of the desktop
int Desktop::width()
{
#ifdef NEPHILIM_WINDOWS	
	return GetSystemMetrics(SM_CXSCREEN);
#endif
	return 0;
}

/// Get the width of the desktop
int Desktop::height()
{
	#ifdef NEPHILIM_WINDOWS
	return GetSystemMetrics(SM_CYSCREEN);
#endif
	
	return 0;
}

NEPHILIM_NS_END