#ifndef RendererGLES2_h__
#define RendererGLES2_h__

#include "Platform.h"
#include "Renderer.h"

NEPHILIM_NS_BEGIN

class NEPHILIM_API RendererGLES2 : public Renderer
{
public:
	RendererGLES2();

	/// Draw a vertex array
	virtual void draw(const VertexArray& varray);

	String getName()
	{
		return "OpenGL ES 2.0";
	} 
};


NEPHILIM_NS_END

#endif // RendererGLES2_h__
