#ifndef PARABOLA_RENDEREROPENGL_H
#define PARABOLA_RENDEREROPENGL_H

#include "Platform.h"
#include "Renderer.h"

NEPHILIM_NS_BEGIN

class NEPHILIM_API RendererOpenGL : public Renderer{
public:

	/// Draw a vertex array
	virtual void draw(const VertexArray2D& varray, const RenderState& state);

	/// This will cancel all shader-related settings and activate the default shader/fixed pipeline
	virtual void setDefaultShader();

	/// Activates the shader for the next drawing calls
	virtual void setShader(Shader& shader);

protected:
	/// Construct the renderer
	RendererOpenGL();
	friend class Surface;

private:
	Shader m_defaultShader;


public:
	/// Clear the bound buffer
	virtual void clear();

	void applyView(const View &view);

	/// Anything that inherits Drawable can be drawn using a renderer
	virtual void draw(Drawable &drawable);

	virtual void drawCube(float x, float y, float z, float len, Color color);

void activateClipRegion(FloatRect rect);
virtual void enableClipping(FloatRect rect);
	virtual void disableClipping();
	virtual void prepare(int w, int h);
	//virtual void drawDebugQuad(float x, float y, float angle, float width, float height, Color color);
	virtual void display();
	virtual void drawDebugTriangleFan(Vec2f* vlist, int vcount, Color color);
	//virtual void drawDebugCircle(Vec2f center, float radius, Vec2f axis, Color color);
	virtual void drawVertexArray(VertexArray2D &vertexArray);
	void drawDebugLine(Vec2f begin, Vec2f end, Color color);	virtual void setProjectionMatrix(const mat4& projection);
	virtual void setViewMatrix(const mat4& view);
	virtual void setModelMatrix(const mat4& model);
};

NEPHILIM_NS_END

#endif