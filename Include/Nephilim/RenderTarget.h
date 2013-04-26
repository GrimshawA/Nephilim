#ifndef RenderTarget_h__
#define RenderTarget_h__

#include "Platform.h"
#include "Vectors.h"

NEPHILIM_NS_BEGIN

class NEPHILIM_API RenderTarget{
public:

	/// Get the size of the render target
	virtual Vec2i getSize() const = 0;
};

NEPHILIM_NS_END
#endif // RenderTarget_h__
