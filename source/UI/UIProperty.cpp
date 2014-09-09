#include <Nephilim/UI/UIProperty.h>

NEPHILIM_NS_BEGIN

UIProperty::UIProperty()
{
}

UIProperty::UIProperty(const String& property)
: m_textProperty(property)
{
}

UIProperty::UIProperty(const Color& colorProperty)
{
	color.r = colorProperty.r;
	color.g = colorProperty.g;
	color.b = colorProperty.b;
	color.a = colorProperty.a;
}

Color UIProperty::getColor()
{
	return Color(color.r, color.g, color.b, color.a);
}

NEPHILIM_NS_END