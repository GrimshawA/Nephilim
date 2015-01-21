#ifndef Drawable_h__
#define Drawable_h__

#include <Nephilim/Platform.h>

NEPHILIM_NS_BEGIN

class GraphicsDevice;
/**	
	\ingroup Graphics
	\class Drawable
	\brief Base class for renderable objects

	All classes that inherit from Drawable can be rendered automatically using
	Renderer::draw(drawable). This will cause onDraw() to be called internally to issue the draw call.

	Drawable derived objects keep their geometry with protected class visibility, so you can inherit from any drawable and fully customize how its geometry is drawn,
	as well as draw additional things.
*/
class Drawable
{
public:

	/// Called to order rendering, when the drawing was issued in the traditional way ( m_renderer->draw(m_sprite) )
	virtual void onDraw(GraphicsDevice* renderer) = 0;
};

NEPHILIM_NS_END
#endif // Drawable_h__