#ifndef CircleShape_h__
#define CircleShape_h__

#include "Platform.h"
#include "Transformable.h"
#include "Drawable.h"
#include "VertexArray2D.h"
#include "Color.h"

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

	virtual void onDraw(Renderer* renderer);

	void setPointCount(int segmentCount);

	void setFillColor(Color color);

	void setRadius(float radius);

	void update();


	VertexArray2D m_vertices;
	float m_radius;
	float m_pointCount;
	Color m_fillColor;
};

NEPHILIM_NS_END

#endif // CircleShape_h__
