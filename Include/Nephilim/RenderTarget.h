#ifndef PARABOLA_RENDERTARGET_H
#define PARABOLA_RENDERTARGET_H

#include "Platform.h"

NEPHILIM_NS_BEGIN

class NEPHILIM_API RenderTarget{
public:

	/// Get the size of the render target
	virtual Vec2i getSize() const = 0;
};

NEPHILIM_NS_END
#endif