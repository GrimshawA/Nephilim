#ifndef NephilimRoundedRectangleShape_h__
#define NephilimRoundedRectangleShape_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Graphics/Transformable.h>
#include <Nephilim/Graphics/Drawable.h>
#include <Nephilim/Graphics/VertexArray2D.h>
#include <Nephilim/Math/Matrix.h>

NEPHILIM_NS_BEGIN
	
/**
	\ingroup Graphics
	\class RoundedRectangleShape
	\brief Rounded rectangle shape with customizable regions
*/
class NEPHILIM_API RoundedRectangleShape : public Drawable, public Transformable
{
public:
	RoundedRectangleShape();

	enum Corners
	{
		TopLeft,
		TopRight,
		BottomLeft,
		BottomRight
	};

	/// Enable or disable roundedness on a specific corner
	void setCornerRounded(Corners corner, bool rounded);

	/// Get the size of the central area of the shape
	vec2 getSize();

	/// Get the full size of the shape, w = centralWidth + cornerRadius*2
	vec2 getFullSize();

	/// Set the size of the central area of the shape
	void setSize(float width, float height);

	/// Set the size of the central area of the shape
	void setSize(vec2 size);

	/// Set the radius of all the corners of the shape
	void setRadius(float radius);

	/// Set the color of all the zones of the shape
	void setColor(const Color& color);

	/// Set the resolution of the corners
	void setCornerPointCount(int count);

	/// Set the outline thickness
	void setOutlineThickness(float thickness);

	/// Set the color of the outline
	void setOutlineColor(const Color& outlineColor);

protected:

	/// Drawable implementation for drawing the shape
	virtual void onDraw(GraphicsDevice* renderer);

	void updateGeometry();

private:
	bool m_geometryDirty;
	int m_cornerPointCount;
	vec2 m_size;
	float m_radius;
	Color m_color;
	Color m_outlineColor;
	VertexArray2D m_geometry;
	VertexArray2D m_outline;
	float m_outlineThickness;

	bool m_topLeftRounded;
	bool m_topRightRounded;
	bool m_bottomLeftRounded;
	bool m_bottomRightRounded;
};

NEPHILIM_NS_END
#endif // NephilimRoundedRectangleShape_h__
