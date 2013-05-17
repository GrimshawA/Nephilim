#ifndef RenderTexture_h__
#define RenderTexture_h__

#include "Platform.h"
#include "Framebuffer.h"
#include "Texture.h"

NEPHILIM_NS_BEGIN

class NEPHILIM_API RenderTexture : public Framebuffer
{
public:

	void create(int width, int height);

	Texture m_texture; ///< The target texture
};

NEPHILIM_NS_END
#endif // RenderTexture_h__
