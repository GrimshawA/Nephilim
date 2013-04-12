#ifndef Renderer_h__
#define Renderer_h__

#include <stack>

#include "Platform.h"
#include "Vectors.h"
#include "Strings.h"
#include "Color.h"
#include "Drawable.h"
#include "VertexArray.h"
#include "View.h"
#include "Shader.h"
#include "RenderModes.h"

#include <map>

NEPHILIM_NS_BEGIN

class RenderTarget;
class Surface;

/**
	\ingroup Graphics
	\class Renderer
	\brief A raw graphics renderer providing a portable way to render primitives
*/
class NEPHILIM_API Renderer{
public:


	/// Every renderer type must declare its name
	virtual String getName() = 0;

	// -- Interface

	// -- Low level calls
	void drawArrays(Render::Primitive::Type primitiveType, int start, int count);
	void enableVertexAttribArray(unsigned int index);
	void disableVertexAttribArray(unsigned int index);
	void setVertexAttribPointer(unsigned int index, int numComponents, int componentType, bool normalized, int stride, const void* ptr);


/*protected:*/
	/// Protected constructor, only the surface can allocate renderers
	Renderer();

	friend class Surface;

	Surface* m_surface;

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
	virtual void drawDebugQuad(float x, float y, float angle, float width, float height, Color color = Color(255,0,1)) {};
	virtual void display() {}; 
	virtual void drawDebugTriangleFan(Vec2f* vlist, int vcount, Color color) {};
	virtual void drawDebugCircle(Vec2f center, float radius, Vec2f axis, Color color){};
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
