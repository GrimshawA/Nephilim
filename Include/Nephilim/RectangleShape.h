#ifndef RectangleShape_h__
#define RectangleShape_h__

#include "Platform.h"
#include "Drawable.h"
#include "VertexArray2D.h"

NEPHILIM_NS_BEGIN

/**
	\ingroup Graphics
	\class RectangleShape
	\brief A drawable rectangle
*/
class NEPHILIM_API RectangleShape : public Drawable
{
public:

protected:

	/// Draw with the renderer.draw(object) syntax
	virtual void onDraw(Renderer* renderer);

	//VertexArray m_
};

NEPHILIM_NS_END
#endif // RectangleShape_h__
