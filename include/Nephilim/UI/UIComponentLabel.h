#ifndef NephilimUIComponentLabel_h__
#define NephilimUIComponentLabel_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Strings.h>
#include <Nephilim/Text.h>
#include <Nephilim/UIComponent.h>

NEPHILIM_NS_BEGIN

class NEPHILIM_API UIComponentText : public UIComponent
{
public:

	enum Alignment
	{
		Left,
		Center,
		Right
	};

	UIComponentText();

	UIComponentText(const String& text, Alignment horizontal = Center, Alignment vertical = Center);

	/// On Attach
	void onAttach(UIView* view);

	void onRender(Renderer* renderer, UIView* view);
	void onPropertySet(const StringList& targetObject, const String& value);
	String m_string;

	Alignment m_horizontal;
	Alignment m_vertical;

	Text text;

	Color color;
};

NEPHILIM_NS_END
#endif // NephilimUIComponentLabel_h__
