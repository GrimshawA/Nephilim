#ifndef NephilimUxScreen_h__
#define NephilimUxScreen_h__

#include <Nephilim/UI/UxNode.h>
#include <Nephilim/Foundation/Color.h>
#include <Nephilim/Foundation/Time.h>

NEPHILIM_NS_BEGIN

class Window;
class GraphicsDevice;
class UxEvent;
class Event;

/**
	\class UxScreen
	\brief Root node of the game's UX render graph

	UX stands for user experience, and classes prefixed by
	Ux are responsible for working together for providing a great user
	experience through the entire game, from intro to closing.
	UX is something higher than UI itself, as its not just about UI, but about
	every little detail about the whole game flow.


	UxScreen is at the root of each GameCore's instance. 
	Basically, UxScreen takes over the entire game window
	and through its completely extensible children, its able
	to render World objects, even with 3D transforms akin to typical widgets,
	all sorts of tools, game consoles, HUD, etc.

	With this unified user experience graph, the animation system works
	in a predictable way and a single set of implemented features is able
	to work over everything in the engine.

	This hierarchy is above everything for a predictable rendering pipeline, 
	where the UI plays nicely with the gaming modules, to make it a beautiful
	unified experience. It also serves purpose as a way to distribute events
	in a well defined order.

	UxScreen represents the entire screen and by populating the screen, we are actually adding renderable elements to it.
	It has a fixed size, equal to the resolution of the game window.

	Coordinate system goes from (0,0) at top left to (size). Remember this is for setting up the screen contents,
	the worlds themselves have their own coordinate systems in 3D.
*/
class NEPHILIM_API UxScreen : public UxNode
{
public:

	/// Game window size
	int width;
	int height;

	Window* window = nullptr;

	/// Need a graphics device to render the screen with
	GraphicsDevice* GDI = nullptr;

	Color clearColor = Color(16,16,16);

public:

	/// Get the object name of this node
	virtual const char* getName();

	/// Get the class name of this node
	virtual const char* getClassName();

	/// Dispatch an event down the hierarchy
	void dispatch(const UxEvent& event);

	/// Take a lower level event directly and translate it into a UxEvent for dispatch()
	void translateAndDispatch(const Event& windowEvent);

	/// This is the primary call, that makes the entire hierarchy draw
	void renderScreen();

	/// This refreshes the screen and its contents with the elapsed time since last call
	void updateScreen(Time time);

	/// Render the entire screen contents
	void render(UxRenderState renderState);
};

NEPHILIM_NS_END
#endif // NephilimUxScreen_h__
