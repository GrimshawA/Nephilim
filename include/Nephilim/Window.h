#ifndef NephilimWindow_h__
#define NephilimWindow_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Strings.h>
#include <Nephilim/Math/Vectors.h>
#include <Nephilim/Event.h>
#include <Nephilim/View.h>
#include <Nephilim/Graphics/RenderTarget.h>

#include <sigc++/sigc++.h>

NEPHILIM_NS_BEGIN

class GraphicsDevice;
class Engine;

typedef void* WindowHandle;
/**
	\ingroup Graphics

	\class Window
	\brief Represents a screen or window where the engine is able to draw graphics

*/
class NEPHILIM_API Window : public sigc::trackable
{
public:
	/// Emitted whenever external files are dropped into this window
	sigc::signal<void, int, int, const StringList&> onDragDrop;

public:
	/// Default constructor
	Window();
		
	/// Destroy the window
	~Window();

	/// Redirect drag and drop listener
	void handleInternalDragDrop(int x, int y, const StringList& fileNames);

	/// Get the width of the screen/window
	int width() const;

	/// Get the height of the screen/window
	int height() const;

	/// Change the size of the window if possible
	void setSize(int width, int height);

	/// Move the window by an amount
	void move(int x, int y);

	/// Attempts to launch a window if applicable
	void create(int screenWidth, int screenHeight);

	void create(void* handle);

	void pushFrame();



	GraphicsDevice* createRenderer();

	/// Default creation of a window
	void create();

	/// Sets the window as active for drawing
	bool setActive(bool flag = true) const;

	/// Convert a point from target coordinates to the view coordinates
	Vec2f convertCoords(const Vec2i &point, const View &view);

	void setMousePosition(Vec2i point);

	/// Get the size of the window
	Vec2i getSize() const;

	/// Discard all pending events
	void discardEvents();

	/// Enable/Disable fullscreen mode
	void setFullscreen(bool enable);

	/// Get the fullscreen mode
	bool getFullscreen();

	/// Swaps buffers
	void swapBuffers();

	WindowHandle getHandle();


	IntRect getViewport(const View& view) const;

	/// Check if there is a pending event
	bool pollEvent(Event &event);

	void setFramerateLimit(int limit);

	/// Sets a new title to the window
	void setTitle(const String &title);

	/// Activate the surface as the active framebuffer
	void activate();

	/// Convert a point in window-space to a homogeneous coordinate
	/// \todo Use viewport data from renderer
	vec2 convertToHomogeneousCoordinate(vec2i point);

	/// Makes the window maximized - windows only
	void maximize();
public:
	class WindowImplementation;
	WindowImplementation* myWindowImpl;

	bool m_fullscreen;
	int m_handle;

	int m_windowWidth, m_windowHeight;

};

class NEPHILIM_API Desktop
{
public:
	/// Get the width of the desktop
	static int width();

	/// Get the width of the desktop
	static int height();

};

NEPHILIM_NS_END

#endif // NephilimWindow_h__