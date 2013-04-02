#include <Nephilim/Framebuffer.h>
#include <Nephilim/CGL.h>

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

/// Attempts to create the framebuffer
bool Framebuffer::create()
{
	bool success = false;

	glGenFramebuffersCGL(1, &static_cast<GLuint>(m_id));

	if(m_id)
	{

	}
	else
		m_id = 0;

	return success;
}

/// Returns the internal id of the currently in-use program by OpenGL
unsigned int Framebuffer::getCurrentActiveFramebuffer()
{
	GLint id;
	glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING_EXT, &id);
	return static_cast<unsigned int>(id);
}

NEPHILIM_NS_END