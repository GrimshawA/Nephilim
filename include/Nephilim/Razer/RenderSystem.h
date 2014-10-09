#ifndef NephilimRenderSystem_h__
#define NephilimRenderSystem_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Razer/System.h>

NEPHILIM_NS_BEGIN
namespace rzr
{

/**
	\class RenderSystem
	\brief Interface for scene renderers

	This is one of the most important classes in the engine,
	it is a RenderSystem that goes through the scene, 2D or 3D,
	and renders it into a final image, which is not an easy task.

	Custom renderers can also be built under plugins easily.	
*/
class NEPHILIM_API RenderSystem : public System
{
public:

};

};
NEPHILIM_NS_END
#endif // NephilimRenderSystem_h__
