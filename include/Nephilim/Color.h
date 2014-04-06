#ifndef NephilimColor_h__
#define NephilimColor_h__

#include "Platform.h"
#include "Vectors.h"

NEPHILIM_NS_BEGIN

/**
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

	/// Creates a color from another color and a custom alpha
	Color(const Color& color, Uint8 alpha);

	/// Return the color in the [0,1] range
	vec4 normalized();

	/// Sums two colors
	Color operator+(const Color& c) const;

	/// Converts a normalized color to a Color
	static Color fromNormalized(const vec4& v);

	static Color Red;         ///< RGBA(x,x,x,x)
	static Color White;       ///<
	static Color Black;
	static Color Green;
	static Color Orange;
	static Color Blue;
	static Color Transparent;
	static Color Grey;
	static Color Yellow;
	static Color Bittersweet;
	static Color Lavender;
	static Color Grass;
	static Color Aqua;

	Uint8 r,g,b,a;
};

class HSVColor
{
public:

	float hue;
	float sat;
	float val;

	Color toRGB();

	static HSVColor RgbToHsv(Color color);

	static HSVColor mix(const HSVColor& c1, const HSVColor& c2);
};

NEPHILIM_NS_END
#endif // NephilimColor_h__