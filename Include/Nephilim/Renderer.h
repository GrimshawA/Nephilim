#ifndef PARABOLA_GRAPHICSRENDERER_H
#define PARABOLA_GRAPHICSRENDERER_H

#include <stack>

#include "Platform.h"
#include "Vectors.h"
#include "Color.h"
#include "Drawable.h"
#include "VertexArray.h"
#include "View.h"
#include "RenderTarget.h"


#include "Text.h"
#include "Strings.h"

PARABOLA_NAMESPACE_BEGIN

class RocketContext;


class PARABOLA_API Renderer{
public:
	Renderer();

	View m_currentView;

	Color m_clearColor;



	/// Activate view and push it to the stack
	void pushView(const View& view);

	/// Pop the current active view
	void popView();

	/// Apply a view
	virtual void applyView(const View &view) = 0;

	/// Set the currently active view
	virtual void setView(const View &view);

	/// Clear the bound buffer
	virtual void clear();

	virtual void drawCube(float x, float y, float z, float len, Color color);


	void setDefaultViewRect(float x, float y);

	void drawDebugText(float x, float y, const String& text)
	{
		Text t;
		t.setString(text);
		t.setPosition(x,y);
		draw(t);
	}

	/// Anything that inherits Drawable can be drawn using a renderer
	virtual void draw(Drawable &drawable) = 0;

	virtual void activateClipRegion(FloatRect rect){}
	virtual void enableClipping(FloatRect rect){};
	virtual void disableClipping(){};
	virtual void prepare(int w, int h) = 0;
	virtual void drawDebugQuad(float x, float y, float angle, float width, float height, Color color = Color(255,0,1)) = 0;
	virtual void display() = 0;
	virtual void drawDebugTriangleFan(Vec2f* vlist, int vcount, Color color) = 0;
	virtual void drawDebugCircle(Vec2f center, float radius, Vec2f axis, Color color) = 0;
	virtual void drawDebugLine(Vec2f begin, Vec2f end, Color color) = 0;

	virtual void drawVertexArray(VertexArray &vertexArray);
	virtual void drawRocketContext(RocketContext* context);

	/// Auto detects an appropriate renderer
	static Renderer* createAutomaticRenderer(RenderTarget* target);

//protected:
	/// The bound render target, where geometry is drawn
	RenderTarget* m_renderTarget;

	std::stack<FloatRect> m_clipRegionStack;

private:
	std::stack<View> m_viewStack;
};

PARABOLA_NAMESPACE_END
#endif