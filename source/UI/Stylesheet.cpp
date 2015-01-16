#include <Nephilim/UI/Stylesheet.h>

NEPHILIM_NS_BEGIN

StyleSheet::StyleArray& StyleSheet::getRule(const String& selector)
{
	for (auto it = selectorList.begin(); it != selectorList.end(); ++it)
	{
		if ((*it) == selector)
		{
			return stylesList[it - selectorList.begin()];
		}
	}
}

//////////////////////////////////////////////////////////////////////////

Color StyleSheet::StyleEntry::toColor()
{
	Color c;

	if (value == "red")
		c = Color::Red;
	else if (value == "blue")
		c = Color::Blue;
	else if (value == "grass")
		c = Color::Grass;

	return c;
}


NEPHILIM_NS_END