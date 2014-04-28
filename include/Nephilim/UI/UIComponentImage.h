#ifndef NephilimUIComponentImage_h__
#define NephilimUIComponentImage_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Strings.h>
#include <Nephilim/UIComponent.h>
#include <Nephilim/Text.h>


NEPHILIM_NS_BEGIN



class NEPHILIM_API UIComponentImage : public UIViewComponent
{
public:
	UIComponentImage(const String& src); /// Load from an image

	void onRender(Renderer* renderer, UIView* view);

	Texture* texture;
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

	Color color;
};

NEPHILIM_NS_END
#endif // NephilimUIComponentImage_h__
