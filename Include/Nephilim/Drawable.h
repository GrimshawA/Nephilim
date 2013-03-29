#ifndef PARABOLA_DRAWABLE_H
#define PARABOLA_DRAWABLE_H

#include "Platform.h"

NEPHILIM_NS_BEGIN

class Renderer;
/**	
	\ingroup Graphics
	Typedef of sf::Drawable to belong to the engine's namespace
*/
class Drawable{
public:
	/// Called to order rendering, when the drawing was issued in the traditional way ( m_renderer->draw(m_sprite) )
	virtual void onDraw(Renderer* renderer) = 0;
};

NEPHILIM_NS_END
#endif