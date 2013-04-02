#include <Nephilim/Framebuffer.h>
#include <Nephilim/CGL.h>
#include <Nephilim/Texture.h>

NEPHILIM_NS_BEGIN

/// Constructs a uninitialized framebuffer
Framebuffer::Framebuffer()
: m_id(0)
{

}

/// Releases the framebuffer
Framebuffer::~Framebuffer()
{

}

/// Bind the framebuffer as the current one
void Framebuffer::bind()
{
	glBindFramebufferCGL(GL_FRAMEBUFFER_CGL, m_id);
}

/// Attaches a texture to the color attachment 0
void Framebuffer::attachTexture(const Texture& texture)
{
	glFramebufferTexture2DCGL(GL_FRAMEBUFFER_CGL, GL_COLOR_ATTACHMENT0_CGL, GL_TEXTURE_2D, texture.m_texture, 0);

	if(glCheckFramebufferStatusCGL(GL_FRAMEBUFFER_CGL) == GL_FRAMEBUFFER_COMPLETE_CGL)
	{
		//TESTLOG("Framebuffer is OK!\n");
	}
}

/// Attempts to create the framebuffer
bool Framebuffer::create()
{
	bool success = false;

	glGenFramebuffersCGL(1, static_cast<GLuint*>(&m_id));

	if(m_id)
	{
		success = true;
	}
	else
		m_id = 0;

	return success;
}

/// Returns the internal id of the currently in-use program by OpenGL
unsigned int Framebuffer::getCurrentActiveFramebuffer()
{
	GLint id;
//	glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING_EXT, &id);
	return static_cast<unsigned int>(id);
}

NEPHILIM_NS_END