#ifndef NephilimRendererGLES2_h__
#define NephilimRendererGLES2_h__

#include "Platform.h"
#include "Renderer.h"

NEPHILIM_NS_BEGIN

class Shader;

/**
	\ingroup Graphics
	\class RendererGLES2
	\brief Renderer specialization for OpenGL ES 2.0
*/
class NEPHILIM_API RendererGLES2 : public Renderer
{
public:
	RendererGLES2();

	/// Draw a vertex array
	virtual void draw(const VertexArray2D& varray, const RenderState& state);

	/// This will cancel all shader-related settings and activate the default shader/fixed pipeline
	virtual void setDefaultShader();

	/// Set the current projection matrix
	virtual void setProjectionMatrix(const mat4& projection);

	/// Set the current view matrix
	virtual void setViewMatrix(const mat4& view);

	/// Set the current model matrix
	virtual void setModelMatrix(const mat4& model);

	//void drawDebugCircle(Vec2f center, float radius, Vec2f axis, Color color);
	void applyView(const View &view);

	Shader m_defaultShader;

};


NEPHILIM_NS_END

#endif // NephilimRendererGLES2_h__
