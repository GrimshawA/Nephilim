#ifndef NephilimGLFramebuffer_h__
#define NephilimGLFramebuffer_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Graphics/GDI/GDI_Framebuffer.h>
#include <Nephilim/Foundation/Vector.h>

NEPHILIM_NS_BEGIN

class GLTexture2D;

/**
	\class Framebuffer
	\brief Manages an OpenGL Framebuffer Object (FBO)

	When you draw primitives with OpenGL, they go through a pipeline until a pixel is output in the end to a framebuffer.
	By default, OpenGL is drawing to buffers that are displayed to the screen. However, this provides a way to draw somewhere else.
	So, when you draw something with a custom framebuffer active, it is drawn in the framebuffer and not in the screen buffer.
	People also refer to this as offscreen rendering or render to texture.

	A framebuffer is not by itself drawable, it needs somewhere to draw to, what we call the attachments.

	The common use for rendering 2D graphics into a texture is to simply attach one texture to the framebuffer and drawing to it.

	Please notice that mobile implementations of OpenGL do not allow to output to more than one attachment, so please make
	sure you know what you're doing if you attempt to go around that for other ends.
*/
class NEPHILIM_API GLFramebuffer : public GDI_Framebuffer
{
public:
	/// Constructs a uninitialized framebuffer
	GLFramebuffer();

	/// Releases the framebuffer
	~GLFramebuffer();

	/// Get the size of the target
	Vec2i getSize() const;

	/// Bind the framebuffer as the current one
	void activate();

	/// Attaches a texture to the color attachment 0
	void attachTexture(const GLTexture2D& texture);

	/// Attempts to create the framebuffer
	bool create();

	/// Check the currently active frame buffer in the context
	static unsigned int getCurrentActiveFramebuffer();

private:
	unsigned int m_id; ///< Internal identifier of the framebuffer
	Vec2i m_size;
};

NEPHILIM_NS_END
#endif // NephilimGLFramebuffer_h__
