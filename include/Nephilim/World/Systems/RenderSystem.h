#ifndef NephilimRenderSystem_h__
#define NephilimRenderSystem_h__

#include <Nephilim/Platform.h>
#include <Nephilim/World/Systems/System.h>

NEPHILIM_NS_BEGIN

class GraphicsDevice;
class GameContent;

/*
	\class RenderingPath
	\brief Base class for implementing world rendering techniques

	This is used to be able to dynamically switch to different rendering techniques
	on runtime. For example, in android we may use a ForwardRenderingPath implementation
	and on PC a DeferredRenderingPath. This is important to counter platform limitations
	and to be able to use the right tool for the job.

	The RenderingPath is responsible for managing and generating its own shader architecture
	for rendering the well defined World data.
*/
class RenderingPath
{
public:

};

class DeferredRenderingPath : public RenderingPath
{

};

/**
	\class RenderSystem
	\brief Interface for scene renderers

	This is one of the most important classes in the engine,
	it is a RenderSystem that goes through the scene, 2D or 3D,
	and renders it into a final image.

	Custom renderers can also be built under plugins easily.
*/
class NEPHILIM_API RenderSystem : public System
{
public:
	bool mWireframe = false;     ///< Render in wireframe mode?
	bool mAllowLighting = true;  ///< Render lights

	GraphicsDevice*        mRenderer = nullptr;
	GameContent*  mContentManager = nullptr;

	/// The current rendering technique for outputting the world into a frame
	RenderingPath* _renderingPath = nullptr;

public:

	/// Callback tells the RenderSystem to produce a frame, based on its watched scene
	virtual void render() = 0;

	/// Enable or disable the wireframe mode
	void setWireframe(bool enable);
};

NEPHILIM_NS_END
#endif // NephilimRenderSystem_h__
