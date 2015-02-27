#ifndef NephilimRazerPostEffectBloom_h__
#define NephilimRazerPostEffectBloom_h__

#include <Nephilim/Graphics/PostEffect.h>
#include <Nephilim/Graphics/Texture2D.h>
#include <Nephilim/Graphics/Shader.h>
#include <Nephilim/Graphics/Framebuffer.h>

NEPHILIM_NS_BEGIN

class GraphicsDevice;

class NEPHILIM_API PostEffectBloom : public PostEffect
{
public:
	PostEffectBloom();

	void apply(GraphicsDevice* renderer, Texture2D& renderTexture);

	void brightnessPass(GraphicsDevice* mRenderer);

	Texture2D	mBrightnessTexture;
	Texture2D	mFirstPassTextures[2];
	Texture2D	mSecondPassTextures[2];

	Framebuffer mBrightnessFramebuffer;

	Shader mBrightnessShader;
};


NEPHILIM_NS_END
#endif // NephilimRazerPostEffectBloom_h__
