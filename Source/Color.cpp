#include <Nephilim/Color.h>

NEPHILIM_NS_BEGIN

// -- List of built-in colors
Color Color::Red = Color(224,7,7,255);
Color Color::White = Color(255,255,255,255);
Color Color::Black = Color(0,0,0,255);
Color Color::Green = Color(30,210,60,255);
Color Color::Orange = Color(255,165,0,255);
Color Color::Blue = Color(30, 144, 255, 255);

Color::Color(){
	r = g = b = 0;
	a = 255;
};

Color::Color(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha){
	r = red;
	g = green;
	b = blue;
	a = alpha;
};


/// Sums two colors
Color& Color::operator+(const Color& c)
{
	return Color(r + c.r, g + c.g, b + c.b, a + c.a);
}

/// Return the color in the [0,1] range
vec4 Color::normalized()
{
	return vec4(static_cast<float>(r) / 255.f, static_cast<float>(g) / 255.f, static_cast<float>(b) / 255.f, static_cast<float>(a) / 255.f);
}

/// Converts a normalized color to a Color
Color Color::fromNormalized(const vec4& v)
{
	return Color(static_cast<Uint8>(v.x * 255.f), static_cast<Uint8>(v.y * 255.f), static_cast<Uint8>(v.z * 255.f), static_cast<Uint8>(v.w * 255.f));
}

NEPHILIM_NS_END