#ifndef NephilimColor_h__
#define NephilimColor_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Math/Vectors.h>

NEPHILIM_NS_BEGIN

/**
	\class Color
	\brief Describes a color in the RGB8888 format
*/
class NEPHILIM_API Color
{
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
	static Color NavyBlue;

	Uint8 r,g,b,a;
};

/**
	\class ColorHSV
	\brief Color value encoded in a Hue, Saturation and Value

	The hue goes from 0 to 360 and it wraps around seamlessly 
	between 0 and 360. This stands for the main tone of the color,
	the vivid hues like Blue, Red, Orange, Purple etc.

	The saturation stands for how much the original hue is pure. The
	less saturation it has, the more it fades to a grey tone. 0 to 1.

	The value is the brightness of the hue, from 0 to 1. At 1 we get
	a fully lit color, and at 0 it fades to black.
*/
class ColorHSV
{
public:
	/// Hue of the color
	float hue;

	/// Saturation of the color
	float sat;

	/// Value of the color
	float val;

	/// Convert to an RGBA color
	Color toRGB();

	/// Convert a RGBA color to an HSV color
	static ColorHSV RgbToHsv(Color color);

	/// Mix two HSV colors together, as if they were ink
	static ColorHSV mix(const ColorHSV& c1, const ColorHSV& c2);
};

NEPHILIM_NS_END
#endif // NephilimColor_h__