#ifndef NephilimRazerPostEffectBloom_h__
#define NephilimRazerPostEffectBloom_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Shader.h>
#include <Nephilim/Texture.h>
#include <Nephilim/Framebuffer.h>
#include <Nephilim/Razer/PostEffect.h>

NEPHILIM_NS_BEGIN
class GraphicsDevice;

namespace rzr
{

class NEPHILIM_API PostEffectBloom : public PostEffect
{
public:
	PostEffectBloom();

	void apply(GraphicsDevice* renderer, Texture& renderTexture);

	void brightnessPass(GraphicsDevice* mRenderer);

	Texture	mBrightnessTexture;
	Texture	mFirstPassTextures[2];
	Texture	mSecondPassTextures[2];

	Framebuffer mBrightnessFramebuffer;

	Shader mBrightnessShader;
};

}
NEPHILIM_NS_END
#endif // NephilimRazerPostEffectBloom_h__
