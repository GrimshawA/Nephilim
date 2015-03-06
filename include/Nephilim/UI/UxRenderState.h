#ifndef NephilimUx_RenderState_h__
#define NephilimUx_RenderState_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Foundation/Matrix.h>

NEPHILIM_NS_BEGIN

/**
	\class UxRenderState
	\brief Structure that carries render information down the UX hierarchy
*/
class NEPHILIM_API UxRenderState
{
public:
	mat4 modelToWorld;
};

NEPHILIM_NS_END
#endif // NephilimUx_RenderState_h__
