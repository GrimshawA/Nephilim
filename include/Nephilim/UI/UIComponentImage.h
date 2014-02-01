#ifndef NephilimUIComponentImage_h__
#define NephilimUIComponentImage_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Strings.h>
#include <Nephilim/UIViewComponent.h>
#include <Nephilim/Text.h>


NEPHILIM_NS_BEGIN

class NEPHILIM_API UIComponentImage : public UIViewComponent
{
public:

};

class NEPHILIM_API UIComponentText : public UIViewComponent
{
public:

	enum Alignment
	{
		Left,
		Center,
		Right
	};

	UIComponentText();

	UIComponentText(const String& text, Alignment horizontal, Alignment vertical);

	/// On Attach
	void onAttach(UIView* view);

	void onRender(Renderer* renderer, UIView* view);

	String m_string;

	Alignment m_horizontal;
	Alignment m_vertical;

	Text text;
};

NEPHILIM_NS_END
#endif // NephilimUIComponentImage_h__
