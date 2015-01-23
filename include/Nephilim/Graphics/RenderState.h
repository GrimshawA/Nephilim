#ifndef RenderState_h__
#define RenderState_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Foundation/Matrix.h>

NEPHILIM_NS_BEGIN

class NEPHILIM_API RenderState
{
public:
	/// Default states
	RenderState();

	/// The model transform to apply
	mat4 m_transform;
};

NEPHILIM_NS_END

#endif // RenderState_h__
