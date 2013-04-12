#ifndef Surface_h__
#define Surface_h__

#include "Platform.h"




#include "Window.h"

NEPHILIM_NS_BEGIN

class Renderer;
class Engine;
/**
	\ingroup Core
	\class Surface
	\brief Represents a renderable frame where the engine is bound to draw on

	This class is responsible to interact and/or control the underlying window

	For example, in Android or iOS, the surface is the screen of the device,
	but Surface does not manage those by itself. However, it can still interact
	with them to give commands or retrieve information.

	In the other hand, in Windows, Linux and OS X, the surface creates a
	full-blown window and manages it entirely.

	As another example, in the browser plugin, the surface is a frame within the
	browser, in which case the surface has to become a child window of that frame,
	put simply.
*/
class NEPHILIM_API Surface
{
public:
	/// Construct the surface object - not yet valid
	Surface(Engine* engine);

	/// Ensure proper destruction
	~Surface();

	int getWidth() const;

	int getHeight() const;

	/// Default creation of a surface
	void create();

	/// Creates and returns the renderer if valid
	Renderer* createRenderer();

	/// Pushes the back buffer to the screen
	void pushFrame();
	
	/// There is one renderer instanced at a time ONLY
	/// The surface instances it as appropriate in order to have multiple gl versions outputs
	Renderer* m_renderer;

	IntRect getViewport(const View& view) const;

	Window* window;
	int m_windowWidth, m_windowHeight;

private:
	Engine*	m_engine; ///< The engine that pairs with this surface
};

NEPHILIM_NS_END

#endif // Surface_h__
