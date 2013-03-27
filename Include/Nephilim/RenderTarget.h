#ifndef PARABOLA_RENDERTARGET_H
#define PARABOLA_RENDERTARGET_H

#include "Platform.h"

PARABOLA_NAMESPACE_BEGIN

class PARABOLA_API RenderTarget{
public:

	/// Get the size of the render target
	virtual Vec2i getSize() const = 0;
};

PARABOLA_NAMESPACE_END
#endif