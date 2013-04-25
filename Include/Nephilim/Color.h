#ifndef PARABOLA_COLOR_H
#define PARABOLA_COLOR_H

#include "Platform.h"
#include "Vectors.h"

NEPHILIM_NS_BEGIN

/*
	\ingroup Graphics
	\class Color
	\brief Describes a color in the RGB8888 format
*/
class NEPHILIM_API Color{
public:
	/// Default color is full-alpha(opaque) black
	Color();

	/// Construct the color of your choice
	Color(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha = 255);

	/// Return the color in the [0,1] range
	vec4 normalized();

	/// Sums two colors
	Color operator+(const Color& c) const;

	/// Converts a normalized color to a Color
	static Color fromNormalized(const vec4& v);

	/// Static Colors
	static Color Red;
	static Color White;
	static Color Black;
	static Color Green;
	static Color Orange;
	static Color Blue;

	Uint8 r,g,b,a;
};

NEPHILIM_NS_END
#endif