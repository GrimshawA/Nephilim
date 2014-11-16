#include <Nephilim/Color.h>
#include <Nephilim/NxMath.h>
#include <Nephilim/Logger.h>
#include <algorithm>

NEPHILIM_NS_BEGIN

using namespace math;

// -- List of built-in colors
Color Color::Red = Color(224,7,7,255);
Color Color::White = Color(255,255,255,255);
Color Color::Black = Color(0,0,0,255);
Color Color::Green = Color(30,210,60,255);
Color Color::Orange = Color(255,165,0,255);
Color Color::Blue = Color(30, 144, 255, 255);
Color Color::Transparent = Color(0, 0, 0, 0);
Color Color::Grey = Color(91, 91, 91, 255);
Color Color::Yellow = Color(212, 197, 36, 255);
Color Color::Bittersweet = Color(212, 197, 36, 255);
Color Color::Lavender = Color(172, 146, 236, 255);
Color Color::Grass = Color(160, 212, 104, 255);
Color Color::Aqua = Color(79, 193, 233, 255);
Color Color::NavyBlue = Color(20, 31, 61, 255);

Color::Color()
{
	r = g = b = 0;
	a = 255;
}

Color::Color(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha)
{
	r = red;
	g = green;
	b = blue;
	a = alpha;
}

Color::Color(const Color& color, Uint8 alpha)
: r(color.r)
, g(color.g)
, b(color.b)
, a(alpha)
{

}

/// Sums two colors
Color Color::operator+(const Color& c) const
{
	Color c2(r + c.r, g + c.g, b + c.b, a + c.a);
	return c2;
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

//////////////////////////////////////////////////////////////////////////
Color HSVColor::toRGB()
{
	float C = val * sat;

	float Hd = hue / 60.f;
	float X = C * (1 - fabs((fmod(Hd,2) - 1)));
	
	float r = 0.f;
	float g = 0.f;
	float b = 0.f;

	if(Hd >= 0 && Hd < 1)
	{
		r = C;
		g = X;
		b = 0;
	}
	else if(Hd >= 1 && Hd < 2)
	{
		r = X;
		g = C;
		b = 0;
	}
	else if(Hd >= 2 && Hd < 3)
	{
		r = 0;
		g = C;
		b = X;
	}
	else if(Hd >= 3 && Hd < 4)
	{
		r = 0;
		g = X;
		b = C;
	}
	else if(Hd >= 4 && Hd < 5)
	{
		r = X;
		g = 0;
		b = C;
	}
	else if(Hd >= 5 && Hd < 6)
	{
		r = C;
		g = 0;
		b = X;
	}

	float M = val - C;

	r += M;
	g += M;
	b += M;

	Color c;

	c.r = r * 255;
	c.g = g * 255;
	c.b = b * 255;

	return c;
}

HSVColor HSVColor::RgbToHsv(Color color)
{
	HSVColor  c;
	c.hue = 0.f;

	float r = (float)color.r / 255.f;
	float g = (float)color.g / 255.f;
	float b = (float)color.b / 255.f;
	
	float Cmax = std::max(r, std::max(g,b));
	float Cmin = std::min(r, std::min(g,b));

	float delta = Cmax - Cmin;

	if(Cmax == r)
	{
		c.hue = 60.f * (fmod( (g - b) / delta, 6));
	}
	else if(Cmax == g)
	{
		c.hue = 60.f * (((b - r) / delta) + 2);
	}
	else if(Cmax == b)
	{
		c.hue = 60.f * (((r - g) / delta) + 4);
	}

	if(delta == 0)
	{
		c.sat = 0.f;
	}
	else
	{
		c.sat = delta / Cmax;
	}

	c.val = Cmax;

	return c;
}

HSVColor HSVColor::mix(const HSVColor& c1, const HSVColor& c2)
{
	HSVColor c3;

	Angle c1Hue = Angle::fromDegrees(c1.hue);
	Angle c2Hue = Angle::fromDegrees(c2.hue);

	Angle newHue = Angle(c1Hue.radians() + Angle::shortestArc(c1Hue, c2Hue).radians() / 2.f);
	newHue.normalize();

	//Log("Mix Hue %f. From %f and %f", newHue.degrees(), c1Hue.degrees(), c2Hue.degrees());

	c3.hue = newHue.degrees();
	c3.sat = 1.f;
	c3.val = 1.f;

	return c3;
}

NEPHILIM_NS_END