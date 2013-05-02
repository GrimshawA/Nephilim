#ifndef RendererOpenGL_h__
#define RendererOpenGL_h__

#include "Platform.h"
#include "Renderer.h"

NEPHILIM_NS_BEGIN

/**
	\ingroup Graphics
	\class RendererOpenGL
	\brief Renderer specialization for desktop platform's OpenGL
*/
class NEPHILIM_API RendererOpenGL : public Renderer
{
public:
	/// Initialize OpenGL renderer
	RendererOpenGL();

	/// Draw a vertex array
	virtual void draw(const VertexArray2D& varray, const RenderState& state);

	/// This will cancel all shader-related settings and activate the default shader/fixed pipeline
	virtual void setDefaultShader();

	/// Activates the shader for the next drawing calls
	virtual void setShader(Shader& shader);

	/// Activate a projection matrix
	virtual void setProjectionMatrix(const mat4& projection);

	/// Activate a view matrix
	virtual void setViewMatrix(const mat4& view);

	/// Activate a model matrix
	virtual void setModelMatrix(const mat4& model);

private:
	Shader m_defaultShader;
};

NEPHILIM_NS_END
#endif // RendererOpenGL_h__