#ifndef PARABOLA_RECT_H
#define PARABOLA_RECT_H

#include "Platform.h"

PARABOLA_NAMESPACE_BEGIN

/**
		\ingroup Foundation
		\class Rect<T>
		\brief Axis-aligned rectangle, specially useful for object boundaries and calculations with them

		IntRect and FloatRect are specializations of Rect<T> for int and float, respectively.
*/
template<typename T>
class PARABOLA_API Rect{
public:
	/// Default rectangle - position (0,0) and size (0,0)
	Rect();

	/// Creates a rectangle from the given coordinates
	Rect(T left, T top, T width, T height);

	/// Checks if a point is within the rect
	bool contains(T x, T y);

	/// Sets the position and dimensions of the rect
	void set(T left, T top, T width, T height);

	/// Move the box relative to its position
	void move(T x, T y);

	/// Set the box position
	void setPosition(T x, T y);

	/// Set the center of the current rect to a new position
	void setCenter(T x, T y);

	/// Check if there is intersection between two rects
	bool intersects(Rect<T> &box);

	T left; ///< The x coordinate of the boundary to the left
	T top; ///< The y coordinate of the boundary to the top of the screen
	T width; ///< Width of the rectangle
	T height; ///< Height of the rectangle
};

typedef Rect<int> IntRect;
typedef Rect<float> FloatRect;

/// Template definitions
#include "Rect.inl"

PARABOLA_NAMESPACE_END
#endif