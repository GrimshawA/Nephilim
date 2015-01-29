#include <Nephilim/Graphics/RenderTexture.h>

NEPHILIM_NS_BEGIN

void RenderTexture::create(int width, int height)
{
	m_texture.create(width, height);
	GLFramebuffer::create();
	GLFramebuffer::attachTexture(m_texture);
}

NEPHILIM_NS_END