#ifndef NephilimSprite_h__
#define NephilimSprite_h__

#include <Nephilim/Platform.h>
#include "Strings.h"

#include "Vectors.h"
#include "Drawable.h"
#include "Transformable.h"

#include "VertexArray2D.h"
#include "Texture.h"

#include <vector>

NEPHILIM_NS_BEGIN

namespace Blend
{
	enum BlendModes
	{
		Add = 0,
		Alpha,
		Multiply
	};
}

class ContentBank;
/**
		\ingroup Graphics
		\class Sprite
		\brief Extends sf::Sprite and implements more functionality.
*/
class NEPHILIM_API Sprite: public Drawable, public Transformable
{
public:
	/// Default sprite
	Sprite();

	/// Safe destruction
	virtual ~Sprite();

	/// Called to order rendering, when the drawing was issued in the traditional way ( m_renderer->draw(m_sprite) )
	virtual void onDraw(GraphicsDevice* renderer);

	/// Set the texture of the sprite
	void setTexture(const Texture &texture, bool resetRect = false);

	void setTexture2(Texture* texture);

	/// Set the texture rect to show
	void setTextureRect(const FloatRect &rect);

	/// Set the color of the sprite
	void setColor(const Color& color);

	Vec2f getPosition() const;

	void setPosition(float x, float y);

	/// Set the position of the sprite
	void setPosition(vec2 position);

	FloatRect getGlobalBounds() const;

	/// Get the binded texture
	const Texture& getTexture();

	/// Returns true if the point is within the sprite's rect
	bool contains(float x, float y);

	/// Resizes the sprite to the selected dimensions using the scale.
	void resize(float x, float y);

	FloatRect getLocalBounds() const;

	const Texture* m_texture;
	VertexArray2D m_vertices;
	FloatRect m_textureRect;

	Blend::BlendModes m_blendMode;


	/*/// Set the position from a vec2f
	/// Position is the top-left coordinate
	void setPosition(Vec2f position);

	/// Set the position from a vec2f
	/// Position is the top-left coordinate
	void setPosition(float x, float y);

	/// Sets the position of the sprite, considering its center instead
	/// Is considered as the center the middle of the local bounding box
	void setCenterPosition(float x, float y);

	/// Sets the position of the sprite, considering its center instead
	/// Is considered as the center the middle of the local bounding box
	void setCenterPosition(Vec2f position);



	/// Check if a point is contained in the sprite
	bool containsPoint(Vec2f point);

	/// Check if a point is contained in the sprite
	bool containsPoint(float x, float y);

	/// Check if the scale factor is negative
	bool isFlippedHorizontally();

	/// Flip the sprite horizontally
	void flipHorizontal();

	/// Check if the scale factor is negative
	bool isFlippedVertically();

	/// Flip the sprite horizontally
	void flipVertical();
*/
};

NEPHILIM_NS_END
#endif //NephilimSprite_h__
