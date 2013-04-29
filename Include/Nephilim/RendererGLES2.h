#ifndef RendererGLES2_h__
#define RendererGLES2_h__

#include "Platform.h"
#include "Renderer.h"

NEPHILIM_NS_BEGIN

class Shader;
class NEPHILIM_API RendererGLES2 : public Renderer
{
public:
	RendererGLES2();

	/// Draw a vertex array
	virtual void draw(const VertexArray2D& varray);

	//void drawDebugCircle(Vec2f center, float radius, Vec2f axis, Color color);
	void applyView(const View &view);

	Shader* m_shader;
};


NEPHILIM_NS_END

#endif // RendererGLES2_h__
