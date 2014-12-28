#ifndef CircleShape_h__
#define CircleShape_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Transformable.h>
#include <Nephilim/Drawable.h>
#include <Nephilim/Graphics/VertexArray2D.h>
#include <Nephilim/Color.h>
#include <Nephilim/Graphics/GLTexture.h>

NEPHILIM_NS_BEGIN

/**
	\ingroup Graphics
	\class CircleShape
	\brief Renderable circle
*/
class NEPHILIM_API CircleShape : public Drawable, public Transformable
{
public:
	CircleShape();

	virtual void onDraw(GraphicsDevice* renderer);

	void setPointCount(int segmentCount);

	void setFillColor(Color color);

	void setTexture(Texture* texture);

	void setTextureCoords(float origin_x, float origin_y, float radius);

	void setRadius(float radius);

	void setOutlineThickness(float thickness);
	void setOutlineColor(Color color);

	void update();


	VertexArray2D m_vertices;
	VertexArray2D m_outlineGeometry;

	bool isDirty;

	float m_radius;
	float m_outlineThickness;
	float m_pointCount;
	float m_beginAngle;
	float m_spanAngle;

	Color m_fillColor;
	Color m_outlineColor;

	Texture* m_texture;
	vec2     m_textureOrigin;
	float    m_textureRadius;
};

NEPHILIM_NS_END

#endif // CircleShape_h__
