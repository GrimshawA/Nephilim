#ifndef NephilimUIStylesheet_h__
#define NephilimUIStylesheet_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Foundation/String.h>
#include <Nephilim/Foundation/Color.h>

#include <vector>

NEPHILIM_NS_BEGIN

/*
	\class StyleSheet
	\brief Contains a set of definitions to style an UI

	A stylesheet is a set of rule blocks, bound to selectors,
	a clever way to match elements
*/
class NEPHILIM_API StyleSheet
{
public:

	class StyleEntry
	{
	public:
		StyleEntry(const String& val)
		{
			value = val;
		}

		Color toColor();

		String value;
	};

	class StyleArray
	{
	public:
		std::vector<std::pair<String, String> > entries;

	public:

		StyleEntry getEntry(const String& entry)
		{
			for (auto it = entries.begin(); it != entries.end(); ++it)
			{
				if ((*it).first == entry)
				{
					return StyleEntry((*it).second);
				}
			}

			return StyleEntry("");
		}

	};

	std::vector<String>     selectorList;
	std::vector<StyleArray> stylesList;

public:

	StyleArray& getRule(const String& selector);

};

NEPHILIM_NS_END
#endif // NephilimUIStylesheet_h__
