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
#include "Matrix.h"

#include <map>

NEPHILIM_NS_BEGIN

class RenderTarget;
class Surface;

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

	/// Effectively binds the "null" shader, which means no shader. Where applicable, this means a fixed-function pipeline.
	void disableShaders();

	/// This will re-activate the pseudo-active shader of the renderer
	/// Useful when shaders are binded manually without using the renderer
	void resetShaders();

	/// Effectively regains control of what texture are bound to all texture units, according to the renderer's data
	void resetTextures();

	void setProjectionMatrix(const mat4& projection);
	void setViewMatrix(const mat4& view);
	void setModelMatrix(const mat4& model);

	mat4 m_projection;
	mat4 m_view;
	mat4 m_model;

protected:
	Type   m_type; ///< The type of this renderer
	String m_name; ///< The string with the name of this renderer
	Surface* m_surface; ///< Guaranteed to be a valid surface while the renderer lives
	bool m_allowShaders; ///< Are shaders enabled at all or fallback to fixed-function/nothing?


	friend class Surface;










public:



	// -- Interface

	// -- Low level calls
	void drawArrays(Render::Primitive::Type primitiveType, int start, int count);
	void enableVertexAttribArray(unsigned int index);
	void disableVertexAttribArray(unsigned int index);
	void setVertexAttribPointer(unsigned int index, int numComponents, int componentType, bool normalized, int stride, const void* ptr);


/*protected:*/
	/// Protected constructor, only the surface can allocate renderers
	


	Shader* m_shader;

	std::map<Render::Primitive::Type, int> m_primitiveTable; 

private:
//	Blend::BlendModes m_blendMode;


public:

	void setModelMatrix(const float* matrix);
	float* modelMatrix;

	/// Draw a vertex array
	virtual void draw(const VertexArray& varray);

	/// Allows a drawable to draw itself
	virtual void draw(Drawable &drawable);



public:



	View m_currentView;

	Color m_clearColor;



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
