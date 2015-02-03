#ifndef NephilimGraphicsSprite_h__
#define NephilimGraphicsSprite_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Graphics/Transformable.h>
#include <Nephilim/Graphics/Drawable.h>
#include <Nephilim/Graphics/VertexArray2D.h>
#include <Nephilim/Foundation/Matrix.h>

NEPHILIM_NS_BEGIN

class Texture2D;

/**
	\class Sprite
	\brief A sprite is defined by a texture and a rectangle section of the texture

	This class is useful for storing all sprites in the game as named resources,
	allowing to instance sprite components from the sprites really easily, without
	nasty tex rect definitions etc.

	This is also used to indicate the world renderers sprite instances that belong to the same source
	and even to hide auto-atlasing optimizations from the gameplay code.
*/
class NEPHILIM_API Sprite
{
public:
	Texture2D* texture;
	FloatRect  texRect;
};

NEPHILIM_NS_END
#endif // NephilimGraphicsSprite_h__
