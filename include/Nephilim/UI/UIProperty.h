#ifndef NephilimUIProperty_h__
#define NephilimUIProperty_h__

#include "Platform.h"
#include "Strings.h"
#include "Color.h"

#include <map>

NEPHILIM_NS_BEGIN

class NEPHILIM_API UIProperty
{
public:
	/// Empty property
	UIProperty();

	/// String property
	UIProperty(const String& property);

	/// Color property
	UIProperty(const Color& colorProperty);

	/// Get the property as a color
	Color getColor();

private:
	struct ColorProperty
	{
		Uint8 r,g,b,a;
	};

	union
	{
		ColorProperty color;
	};

	String m_textProperty;
};

typedef std::map<String, UIProperty> UIPropertyMap;

NEPHILIM_NS_END
#endif // NephilimUIProperty_h__
