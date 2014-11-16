#ifndef NephilimRazerSystemRenderer_h__
#define NephilimRazerSystemRenderer_h__

#include <Nephilim/Platform.h>
#include <Nephilim/World/RenderSystem.h>
#include <Nephilim/Graphics/GraphicsDevice.h>

#include <Nephilim/Graphics/Framebuffer.h>
#include <Nephilim/Graphics/GLTexture.h>
#include <Nephilim/ContentManager.h>
#include <Nephilim/World/PostEffect.h>

NEPHILIM_NS_BEGIN
namespace rzr
{

class Entity;

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
	RenderSystemDefault();

	void getActiveCamera(vec3& position, mat4& proj, mat4& view);

	/// This function will initialize the frame buffer and other things in order to produce a new frame out of the scene
	void startFrame();

	/// This function will basically truncate the output buffer and apply any post processing needed, generating the final composite
	void endFrame();

	/// All this function does is to render the current rendered scene frame to the backbuffer
	void drawToBackBuffer();

	virtual void update(const Time& deltaTime);
	virtual void render();

	/// Render scene gets all scene render data and outputs it to the active target
	void renderScene();
	
	void renderTilemap(Entity& entity);
	void renderMesh(Entity& entity);
	void renderModel(Entity& entity);

	void renderAllSprites();




	Texture mRenderTexture; ///< The final scene render goes here
	Framebuffer mFramebuffer;

	int mTargetWidth;
	int mTargetHeight;

	/// Preliminary list of post effects
	std::vector<PostEffect*> mPostEffects;
};

};
NEPHILIM_NS_END
#endif // NephilimRazerSystemRenderer_h__
