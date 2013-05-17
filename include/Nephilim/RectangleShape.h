#ifndef RectangleShape_h__
#define RectangleShape_h__

#include "Platform.h"
#include "Drawable.h"
#include "Color.h"
#include "Transformable.h"
#include "VertexArray2D.h"

NEPHILIM_NS_BEGIN

class Texture;

/**
	\ingroup Graphics
	\class RectangleShape
	\brief A drawable rectangle
*/
class NEPHILIM_API RectangleShape : public Drawable, public Transformable
{
public:
	RectangleShape();

	void setSize(float width, float height);

	void setColor(const Color& color);

	void setColors(const Color& topleft, const Color& topright, const Color& bottomright, const Color& bottomleft);

	void setTexture(Texture* texture);

	/// Set the sub region of the texture to display. These coordinates are in pixels and are normalized internally
	void setTextureRect(float left, float top, float width, float height);

	/// Invert the vertical coordinates of the texture - hacky
	void invertTextureCoordinates();

protected:

	/// Draw with the renderer.draw(object) syntax
	virtual void onDraw(Renderer* renderer);

	VertexArray2D m_geometry;
	VertexArray2D m_outline;

	Texture* m_texture;
};

NEPHILIM_NS_END
#endif // RectangleShape_h__
