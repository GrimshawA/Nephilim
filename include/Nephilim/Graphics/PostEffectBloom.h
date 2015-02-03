#ifndef NephilimRazerPostEffectBloom_h__
#define NephilimRazerPostEffectBloom_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Graphics/GL/GLShader.h>
#include <Nephilim/Graphics/GL/GLTexture.h>
#include <Nephilim/Graphics/GL/GLFramebuffer.h>

#include <Nephilim/Graphics/PostEffect.h>

NEPHILIM_NS_BEGIN
class GraphicsDevice;

class NEPHILIM_API PostEffectBloom : public PostEffect
{
public:
	PostEffectBloom();

	void apply(GraphicsDevice* renderer, Texture& renderTexture);

	void brightnessPass(GraphicsDevice* mRenderer);

	Texture	mBrightnessTexture;
	Texture	mFirstPassTextures[2];
	Texture	mSecondPassTextures[2];

	GLFramebuffer mBrightnessFramebuffer;

	GLShader mBrightnessShader;
};


NEPHILIM_NS_END
#endif // NephilimRazerPostEffectBloom_h__
