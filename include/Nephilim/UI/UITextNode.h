#ifndef NephilimUI_TextNode_h__
#define NephilimUI_TextNode_h__

#include <Nephilim/UI/UIView.h>
#include <Nephilim/Graphics/Text.h>

NEPHILIM_NS_BEGIN

/**
	\class UITextNode
	\brief Displays a text with wrapping and selecting
*/
class NEPHILIM_API UITextNode : public UIView
{
public:

	enum Alignment
	{
		Left,
		Center,
		Right
	};

	UITextNode();

	UITextNode(const String& text, Alignment horizontal = Center, Alignment vertical = Center);


	void onRender(GraphicsDevice* renderer, UIView* view, const mat4& parentTransform);

	void onPropertySet(const StringList& targetObject, const String& value);

	String m_string;

	Alignment m_horizontal;
	Alignment m_vertical;

	Text text;

	Color color;
};

NEPHILIM_NS_END
#endif // NephilimUI_TextNode_h__
