#include <Nephilim/RenderTexture.h>

NEPHILIM_NS_BEGIN

void RenderTexture::create(int width, int height)
{
	m_texture.create(width, height);
	Framebuffer::create();
	Framebuffer::attachTexture(m_texture);
}

NEPHILIM_NS_END