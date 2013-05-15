#include <Nephilim/RenderStateBackup.h>
#include <Nephilim/Texture.h>
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

NEPHILIM_NS_END