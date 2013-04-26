#ifndef Renderer_h__
#define Renderer_h__

#include <stack>

#include "Platform.h"
#include "Strings.h"
#include "Vectors.h"
#include "Strings.h"
#include "Color.h"
#include "Drawable.h"
#include "VertexArray.h"
#include "View.h"
#include "Shader.h"
#include "RenderModes.h"
#include "RenderState.h"
#include "Matrix.h"

#include <map>

NEPHILIM_NS_BEGIN

class RenderTarget;
class Surface;
class Framebuffer;

/**
	\ingroup Graphics
	\class Renderer
	\brief A raw graphics renderer providing a portable way to render primitives

	Drawing Vertex Array based drawable with custom shaders:
	- Vertex attributes are activated at location 0, 1 and 2, respectively for Position, Color and Texture coordinates.
	- Have model and projection matrices in your vertex shader if you want them to be set with the camera and world transform of
	  the drawable
	- Textures are activated at texture unit 0, as default
	- Whether the vertex array is textured or not, a uniform int textured variable will be set with 1 or 0, for true or false.
*/
class NEPHILIM_API Renderer
{
public:
	/// Base constructor - virtual class 
	Renderer();

	/// Enumerates all types of native renderers
	enum Type
	{
		OpenGL,		///< Desktop OpenGL
		OpenGLES1,  ///< Mobile OpenGL ES 1.1
		OpenGLES2,  ///< Mobile OpenGL ES 2.0
		Other		///< Any other user-defined renderer
	};

	/// Get the type of this renderer
	Type getType();

	/// Get the full name of this renderer
	String getName();

	/// Draw a debug quad with the given color,angle and dimensions - slow
	void drawDebugQuad(float x, float y, float angle, float width, float height, Color color = Color(255,0,1));

	/// Draw a debug circle with the given color and radius - slow
	void drawDebugCircle(Vec2f center, float radius, Vec2f axis, Color color);

	/// Draw a vertex array
	virtual void draw(const VertexArray& varray, const RenderState& state = RenderState());

	/// Allows a drawable to draw itself
	virtual void draw(Drawable &drawable);

	/// Set the clear color of the render target
	virtual void setClearColor(const Color& color);

	/// Get the current clear color
	virtual Color getClearColor();

	/// Activates the default render target
	/// This means that rendering will now happen in the visible window
	virtual void setDefaultTarget();

	/// Activates a different render target for rendering
	virtual void setFramebuffer(Framebuffer& target);

	/// Set the current transform matrices to identity (projection, view and model)
	/// This is the default OpenGL state, an orthogonal projection on a [-1, -1, 1, 1] rectangle
	virtual void setDefaultTransforms();

	/// Set the default view port, matches exactly the size of the current target
	virtual void setDefaultViewport();

	/// Set the viewport in target-relative coordinates
	/// If you want to set the viewport in pixels, use setViewportInPixels()
	virtual void setViewport(float left, float bottom, float width, float height);

	/// Set the viewport as in glViewport()
	virtual void setViewportInPixels(float left, float bottom, float width, float height);

	/// Activates blending with the default mode: Alpha
	virtual void setDefaultBlending();

	/// Activates blending and a blend mode
	virtual void setBlendMode(Render::Blend::Mode mode);

	/// Activates or deactivates blending entirely
	virtual void setBlendingEnabled(bool enable);

	/// This will cancel all shader-related settings and activate the default shader/fixed pipeline
	virtual void setDefaultShader();

	/// Activates the shader for the next drawing calls
	virtual void setShader(Shader& shader);

	/// Activates or deactivates rectangular clipping - scissor test
	virtual void setClippingEnabled(bool enable);

	/// Effectively regains control of what texture are bound to all texture units, according to the renderer's data
	void resetTextures();

	virtual void setProjectionMatrix(const mat4& projection);
	virtual void setViewMatrix(const mat4& view);
	virtual void setModelMatrix(const mat4& model);

	mat4 m_projection;
	mat4 m_view;
	mat4 m_model;

	Shader* m_activeShader;

protected:
	Type   m_type; ///< The type of this renderer
	String m_name; ///< The string with the name of this renderer
	Surface* m_surface; ///< Guaranteed to be a valid surface while the renderer lives
	RenderTarget* m_target; ///< The frame buffer being drawn to, either equals the surface or a custom created FBO
	Color m_clearColor; ///< The color of the background when clearing buffer

	friend class Surface;










public:



	// -- Interface

	// -- Low level calls
	void drawArrays(Render::Primitive::Type primitiveType, int start, int count);
	void enableVertexAttribArray(unsigned int index);
	void disableVertexAttribArray(unsigned int index);
	void setVertexAttribPointer(unsigned int index, int numComponents, int componentType, bool normalized, int stride, const void* ptr);

	Shader* m_shader;

	std::map<Render::Primitive::Type, int> m_primitiveTable;



public:



	View m_currentView;

	



	/// Activate view and push it to the stack
	void pushView(const View& view);

	/// Pop the current active view
	void popView();

	/// Apply a view
	virtual void applyView(const View &view){};

	/// Set the currently active view
	virtual void setView(const View &view);

	/// Clear the bound buffer
	virtual void clear();

	virtual void drawCube(float x, float y, float z, float len, Color color);

	void setDefaultViewRect(float x, float y);



	virtual void activateClipRegion(FloatRect rect){}
	virtual void enableClipping(FloatRect rect){};
	virtual void disableClipping(){};
	virtual void prepare(int w, int h) {};
	virtual void display() {}; 
	virtual void drawDebugTriangleFan(Vec2f* vlist, int vcount, Color color) {};
	
	virtual void drawDebugLine(Vec2f begin, Vec2f end, Color color){};

	virtual void drawVertexArray(VertexArray &vertexArray);

	/// Auto detects an appropriate renderer
	static Renderer* createAutomaticRenderer(RenderTarget* target);
	 
	std::stack<FloatRect> m_clipRegionStack;

	std::stack<View> m_viewStack;

	RenderTarget* m_renderTarget;
};

NEPHILIM_NS_END
#endif // Renderer_h__
