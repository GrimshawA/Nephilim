#ifndef NephilimRazerSystemRenderer_h__
#define NephilimRazerSystemRenderer_h__

#include <Nephilim/Platform.h>

#include <Nephilim/Foundation/Transform.h>


#include <Nephilim/World/Systems/RenderSystem.h>
#include <Nephilim/World/ASpriteComponent.h>

#include <Nephilim/Graphics/GraphicsDevice.h>
#include <Nephilim/Graphics/Framebuffer.h>
#include <Nephilim/Graphics/Texture2D.h>

#include <Nephilim/Game/GameContent.h>

NEPHILIM_NS_BEGIN

class Entity;
class AStaticMeshComponent;

/**
	\class SystemRenderer
	\brief Native scene renderer of Nephilim

	The sole responsability of this system is to hook to any scene
	and produce a final image of it using a graphics API.

	It may or may not implement optimizing structures and
	multiple render paths. It is configurable.

	Users are also free to implement any other renderer system
	to render things their own way.

	Usually, this system will produce the final render based on the
	active camera, post processing effects and other settings.

	Optionally, it can also render directly to the screen when there are 
	no post processing steps required. (better performance on android would be a use case)
*/
class NEPHILIM_API RenderSystemDefault : public RenderSystem
{
public:

	Texture2D mRenderTexture; ///< The final scene render goes here

	Framebuffer mFramebuffer;

	/// Current world framebuffer resolution
	int mTargetWidth;

	/// Current world framebuffer resolution
	int mTargetHeight;

public:


	RenderSystemDefault();

	/// Draw a static mesh component
	void Render(AStaticMeshComponent* mesh);

	/// This function will initialize the frame buffer and other things in order to produce a new frame out of the scene
	void startFrame();

	/// This function will basically truncate the output buffer and apply any post processing needed, generating the final composite
	void endFrame();

	/// All this function does is to render the current rendered scene frame to the backbuffer
	void drawToBackBuffer();

	virtual void render();

	/// Render scene gets all scene render data and outputs it to the active target
	void renderScene();

	/// Render a sky box into the map
	void renderSkyBox();

	void renderAllSprites();

	void renderSprite(ASpriteComponent* sprite);


};

NEPHILIM_NS_END
#endif // NephilimRazerSystemRenderer_h__
