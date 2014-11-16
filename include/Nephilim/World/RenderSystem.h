#ifndef NephilimRenderSystem_h__
#define NephilimRenderSystem_h__

#include <Nephilim/Platform.h>
#include <Nephilim/World/System.h>

NEPHILIM_NS_BEGIN

class GraphicsDevice;
class ContentManager;

/**
	\class RenderSystem
	\brief Interface for scene renderers

	This is one of the most important classes in the engine,
	it is a RenderSystem that goes through the scene, 2D or 3D,
	and renders it into a final image.

	Custom renderers can also be built under plugins easily.	
*/
class NEPHILIM_API RenderSystem : public rzr::System
{
public:
	bool mWireframe = false;     ///< Render in wireframe mode?
	bool mAllowLighting = true;  ///< Render lights?

	GraphicsDevice*        mRenderer = nullptr;
	ContentManager*  mContentManager = nullptr;

public:

	/// Callback tells the RenderSystem to produce a frame, based on its watched scene
	virtual void render() = 0;

	/// Enable or disable the wireframe mode
	void setWireframe(bool enable);
};

NEPHILIM_NS_END
#endif // NephilimRenderSystem_h__
