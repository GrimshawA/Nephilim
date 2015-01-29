#ifndef NephilimGraphicsDebugDraw_h__
#define NephilimGraphicsDebugDraw_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Graphics/Transformable.h>
#include <Nephilim/Graphics/Drawable.h>
#include <Nephilim/Graphics/VertexArray2D.h>
#include <Nephilim/Foundation/Color.h>
#include <Nephilim/Graphics/GL/GLTexture.h>

NEPHILIM_NS_BEGIN

/**
	\class DebugDraw
	\brief Able to render primitives into the scene for prototyping purposes
*/
class NEPHILIM_API DebugDraw
{
public:
	GraphicsDevice* _graphics = nullptr;

public:

	DebugDraw(GraphicsDevice* graphics);

	/// Draw a colored box
	void drawBox(float x, float y, float z, float size, Color a);
};

NEPHILIM_NS_END

#endif // NephilimGraphicsDebugDraw_h__
