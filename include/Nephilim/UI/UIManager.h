#ifndef NephilimUIManager_h__
#define NephilimUIManager_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Strings.h>

#include <vector>

NEPHILIM_NS_BEGIN

class GraphicsDevice;
class UICanvas;

/**
	\class UIManager
	\brief Manages the canvases for UI

	This object aims to hold all instanced
	UICanvas through the entire application at any given
	time.

	This is so the game can control all the UI in special ways,
	in a global scope, as well as properly deallocate all of it
	on exit.

	Many canvases can be instanced at once for many uses,
	some can be active, others dormant, but still on memory.

	In-world UI will also be tracked through here usually
*/
class NEPHILIM_API UIManager
{
public:

	/// Create a new canvas, uniquely named
	UICanvas* createCanvas(const String& name);

	std::vector<UICanvas*> canvasList;
};

NEPHILIM_NS_END
#endif // NephilimUIManager_h__
