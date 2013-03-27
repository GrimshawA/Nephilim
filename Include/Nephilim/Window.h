#ifndef PARABOLA_WINDOW_H
#define PARABOLA_WINDOW_H

#include "Platform.h"
#include "Strings.h"
#include "Vectors.h"
#include "Event.h"
#include "View.h"
#include "RenderTarget.h"

PARABOLA_NAMESPACE_BEGIN

typedef void* WindowHandle;
/**
	\ingroup Graphics

	\class Window
	\brief Represents a screen or window where the engine is able to draw graphics

*/
class PARABOLA_API Window : public RenderTarget{
public:
	/// Default constructor
	Window();
		
	/// Destroy the window
	~Window();

	/// Attempts to launch a window if applicable
	void create(int screenWidth, int screenHeight);

	void create(void* handle);

	/// Sets the window as active for drawing
	bool setActive(bool flag = true) const;

	/// Convert a point from target coordinates to the view coordinates
	Vec2f convertCoords(const Vec2i &point, const View &view);

	void setMousePosition(Vec2i point);

	/// Get the width of the screen/window
	int getWidth() const;

	/// Get the height of the screen/window
	int getHeight() const;

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


public:
	class WindowImplementation;
	WindowImplementation* myWindowImpl;

	bool m_fullscreen;
	int m_handle;
};

PARABOLA_NAMESPACE_END
#endif