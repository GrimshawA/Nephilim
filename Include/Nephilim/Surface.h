#ifndef Surface_h__
#define Surface_h__

#include "Platform.h"




#include "Window.h"

NEPHILIM_NS_BEGIN

/**
	\ingroup Core
	\class Surface
	\brief Represents a renderable frame where the engine is bound to draw on
*/
class NEPHILIM_API Surface
{
public:

	/// Default creation of a surface
	void create();

	Window* window;
};

NEPHILIM_NS_END

#endif // Surface_h__
