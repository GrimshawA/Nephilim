#ifndef NephilimRenderer_h__
#define NephilimRenderer_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Strings.h>
#include <Nephilim/Vectors.h>
#include <Nephilim/Strings.h>
#include <Nephilim/Color.h>
#include <Nephilim/Drawable.h>
#include <Nephilim/VertexArray2D.h>
#include <Nephilim/View.h>
#include <Nephilim/Shader.h>
#include <Nephilim/RenderModes.h>
#include <Nephilim/RenderState.h>
#include <Nephilim/Matrix.h>
#include <Nephilim/Texture.h>

#include <map>
#include <stack>

NEPHILIM_NS_BEGIN

class RenderTarget;
class Surface;
class Image;
class VertexArray;

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
class NEPHILIM_API GraphicsDevice
{
public:
	friend class Surface;
	
	/// Enumerates all types of native renderers
	enum Type
	{
		OpenGL,		///< Desktop OpenGL
		OpenGLES1,  ///< Mobile OpenGL ES 1.1
		OpenGLES2,  ///< Mobile OpenGL ES 2.0
		Other		///< Any other user-defined renderer
	};

	/// Base constructor - virtual class 
	GraphicsDevice();

	/// Get the type of this renderer
	Type getType();

	/// Get the full name of this renderer
	String getName();

	/// Get the current surface
	Surface& getSurface();

	/// Set an hint to the renderer which tells it to prefer shaders by default(true), or to use the fixed pipeline instead
	/// By default, it means a direction relation with setDefaultShader(). Applies only to platforms with both options available.
	void setShaderUsageHint(bool allow);

	/// Draw a debug quad with the given color,angle and dimensions - slow
	void drawDebugQuad(float x, float y, float angle, float width, float height, Color color = Color(255,0,1));

	/// Draw a debug circle with the given color and radius - slow
	void drawDebugCircle(Vec2f center, float radius, Vec2f axis, Color color);

	/// Draw a debug line with the given color - slow
	void drawDebugLine(Vec2f begin, Vec2f end, Color color);

	/// Push client-side geometry to the GPU
	/// This is usually slower than using a VBO because the data is uploaded to the GPU every time
	virtual void draw(const VertexArray& vertexData);

	/// Draw a vertex array
	virtual void draw(const VertexArray2D& varray, const RenderState& state = RenderState());

	/// Allows a drawable to draw itself
	virtual void draw(Drawable &drawable);

	/// Clears the depth buffer
	virtual void clearDepthBuffer();

	/// Clears the stencil buffer
	virtual void clearStencilBuffer();

	/// Clears the color buffer
	virtual void clearColorBuffer();

	/// Combines all clearXBuffer() calls
	virtual void clearAllBuffers();

	/// Set the clear color of the render target
	virtual void setClearColor(const Color& color);

	/// Get the current clear color
	virtual Color getClearColor();

	/// Binds the default 1x1 full white texture at texture unit 0
	virtual void setDefaultTexture();

	/// Activates the default render target
	/// This means that rendering will now happen in the visible window
	virtual void setDefaultTarget();

	/// Activates a different render target for rendering
	virtual void setTarget(RenderTarget& target);

	/// Set the current transform matrices to identity (projection, view and model)
	/// This is the default OpenGL state, an orthogonal projection on a [-1, -1, 1, 1] rectangle
	virtual void setDefaultTransforms();

	/// Set the default view port, matches exactly the size of the current target
	virtual void setDefaultViewport();

	/// Set the viewport in target-relative coordinates
	/// If you want to set the viewport in pixels, use setViewportInPixels()
	virtual void setViewport(float left, float top, float width, float height);

	/// Set the viewport as in glViewport(), but specify coordinates from top-left of the window instead
	virtual void setViewportInPixels(int left, int top, int width, int height);

	/// Set the default depth test mode: false
	virtual void setDefaultDepthTesting();

	/// Sets the z-buffer depth testing to enabled or not
	virtual void setDepthTestEnabled(bool enable);

	/// Activates blending with the default mode: Alpha
	virtual void setDefaultBlending();

	/// Activates blending and a blend mode
	virtual void setBlendMode(Render::Blend::Mode mode);

	/// Activates or deactivates blending entirely
	virtual void setBlendingEnabled(bool enable);

	/// This will cancel all shader-related settings and activate the default shader/fixed pipeline
	virtual void setDefaultShader();

	/// Orders the renderer to reload the default shader
	virtual void reloadDefaultShader();

	/// Activates the shader for the next drawing calls
	virtual void setShader(Shader& shader);

	/// Activates or deactivates rectangular clipping - scissor test
	virtual void setClippingEnabled(bool enable);

	/// Resets the scissor clipping rectangle to the full target
	virtual void resetClippingRect();

	/// Set the scissor clipping rectangle, it cannot exceed the current rectangle
	/// You can only request a sub-region of the current clipping area, unless you call resetClippingRect() first
	virtual void setClippingRect(FloatRect rect);

	///
	virtual void pushClippingRect(FloatRect rect, bool isNormalized = false);

	///
	virtual void popClippingRect();

	/// Set the current projection matrix
	virtual void setProjectionMatrix(const mat4& projection);

	/// Set the current view matrix
	virtual void setViewMatrix(const mat4& view);

	/// Set the current model matrix
	virtual void setModelMatrix(const mat4& model);

	/// Get a current renderer-global matrix
	mat4 getProjectionMatrix();

	/// Get a current renderer-global matrix
	mat4 getViewMatrix();

	/// Get a current renderer-global matrix
	mat4 getModelMatrix();

	/// Capture the currently bound frame buffer pixles to an image
	bool readPixels(Image& image);

	/// Orders the renderer to reload the default texture etc
	void reloadResources();

	// -- Low level calls

	/// Mimics glDrawArrays()
	void drawArrays(Render::Primitive::Type primitiveType, int start, int count);

	/// Mimics glEnableVertexAttribArray()
	void enableVertexAttribArray(unsigned int index);

	/// Mimics glDisableVertexAttribArray()
	void disableVertexAttribArray(unsigned int index);

	/// Mimics glVertexAttribPointer()
	void setVertexAttribPointer(unsigned int index, int numComponents, int componentType, bool normalized, int stride, const void* ptr);

protected:
	Type                  m_type;            ///< The type of this renderer
	String                m_name;            ///< The string with the name of this renderer
	Surface*              m_surface;         ///< Guaranteed to be a valid surface while the renderer lives
	RenderTarget*         m_target;          ///< The frame buffer being drawn to, either equals the surface or a custom created FBO
	Color                 m_clearColor;      ///< The color of the background when clearing buffer
	FloatRect             m_scissorRect;     ///< If scissor clipping is enabled, this is the rect being used
	mat4                  m_projection;      ///< Current projection matrix
	mat4                  m_view;            ///< Current view matrix
	mat4                  m_model;           ///< Current model matrix
	Shader*               m_activeShader;    ///< Current active shader
	bool		          m_shaderUsageHint; ///< Hint for the default shader usage
	Texture		          m_defaultTexture;  ///< Full white 1x1 default texture
	std::stack<FloatRect> m_scissorStack;    ///< Stack of scissor test regions

	/// Conversion table of Render::Primitive::Type to GLenum
	std::map<Render::Primitive::Type, int> m_primitiveTable;	
};

NEPHILIM_NS_END
#endif // NephilimRenderer_h__
