#ifndef Framebuffer_h__
#define Framebuffer_h__

#include "Platform.h"

NEPHILIM_NS_BEGIN

/**
	\ingroup Graphics
	\class Framebuffer
	\brief Manages an OpenGL Framebuffer Object (FBO)
*/
class NEPHILIM_API Framebuffer
{
public:
	/// Constructs a uninitialized framebuffer
	Framebuffer();

	/// Releases the framebuffer
	~Framebuffer();

	/// Bind the framebuffer as the current one
	void bind();

	/// Attempts to create the framebuffer
	bool create();

	/// Check the currently active frame buffer in the context
	static unsigned int getCurrentActiveFramebuffer();

private:
	unsigned int m_id; ///< Internal identifier of the framebuffer
};

NEPHILIM_NS_END
#endif // Framebuffer_h__
