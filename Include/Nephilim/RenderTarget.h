#ifndef RenderTarget_h__
#define RenderTarget_h__

#include "Platform.h"
#include "Vectors.h"

NEPHILIM_NS_BEGIN

/**
	\ingroup Graphics
	\class RenderTarget
	\brief OpenGL targets for rendering

	A RenderTarget is basically an abstract surface with a width and a height where OpenGL can draw graphics.

	There two types of RenderTargets: 
		- Surface (the actual final window where we can see the graphics)
		- Framebuffer (an off screen target to draw to textures)
*/
class NEPHILIM_API RenderTarget{
public:
	/// Get the size of the render target
	virtual Vec2i getSize() const = 0;

	/// Activates the render target for rendering
	virtual void activate() = 0;
};

NEPHILIM_NS_END
#endif // RenderTarget_h__
