#ifndef RenderTexture_h__
#define RenderTexture_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Graphics/GL/GLFramebuffer.h>
#include <Nephilim/Graphics/GL/GLTexture.h>

NEPHILIM_NS_BEGIN

class NEPHILIM_API RenderTexture : public GLFramebuffer
{
public:

	void create(int width, int height);

	Texture m_texture; ///< The target texture
};

NEPHILIM_NS_END
#endif // RenderTexture_h__
