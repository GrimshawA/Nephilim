#include <Nephilim/Graphics/RenderStateBackup.h>
#include <Nephilim/Graphics/GLTexture.h>
#include <Nephilim/Graphics/GraphicsDevice.h>
#include <Nephilim/CGL.h>

NEPHILIM_NS_BEGIN

TextureBackup::TextureBackup()
: id(Texture::getCurrentBoundTexture())
{

}

TextureBackup::~TextureBackup()
{
	glBindTexture(GL_TEXTURE_2D, id);
}

RendererTransformBackup::RendererTransformBackup(GraphicsDevice* renderer)
: m_renderer(renderer)
{
	if(m_renderer)
	{
		p = m_renderer->getProjectionMatrix();
		v = m_renderer->getViewMatrix();
		m = m_renderer->getModelMatrix();
	}
}

RendererTransformBackup::~RendererTransformBackup()
{
	if(m_renderer)
	{
		m_renderer->setProjectionMatrix(p);
		m_renderer->setViewMatrix(v);
		m_renderer->setModelMatrix(m);
	}
}

NEPHILIM_NS_END