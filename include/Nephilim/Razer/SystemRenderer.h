#ifndef NephilimRazerSystemRenderer_h__
#define NephilimRazerSystemRenderer_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Razer/System.h>
#include <Nephilim/Renderer.h>
#include <Nephilim/Framebuffer.h>
#include <Nephilim/Texture.h>
#include <Nephilim/ContentManager.h>
#include <Nephilim/Razer/PostEffect.h>

NEPHILIM_NS_BEGIN
namespace rzr
{

class Entity;

class NEPHILIM_API SystemRenderer : public System
{
public:
	SystemRenderer();

	virtual void update(const Time& deltaTime);
	virtual void render();
	
	void renderTilemap(Entity& entity);
	void renderMesh(Entity& entity);
	void renderModel(Entity& entity);

	Renderer*        mRenderer;
	ContentManager*  mContentManager;


	Texture mRenderTexture;
	Framebuffer mFramebuffer;



	/// Preliminary list of post effects
	std::vector<PostEffect*> mPostEffects;
};

};
NEPHILIM_NS_END
#endif // NephilimRazerSystemRenderer_h__
