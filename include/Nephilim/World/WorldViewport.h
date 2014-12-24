#ifndef NephilimWorldViewport_h__
#define NephilimWorldViewport_h__

#include <Nephilim/Platform.h>
#include <Nephilim/World/Camera.h>

NEPHILIM_NS_BEGIN

class Viewport
{
public:
	int left, top, right, bottom;
};

/**
	\class WorldViewport
	\brief A viewport target to draw the world on

	For example, a split screen game would basically have 2 or more
	WorldViewports active, so the world is output into all those targets
	with different cameras.
*/
class NEPHILIM_API WorldViewport
{
public:
	Viewport _viewport;  ///< Viewport to draw to
	Camera   _camera;    ///< Camera to use
};

NEPHILIM_NS_END
#endif // NephilimWorldViewport_h__
