#ifndef NephilimUIText_h__
#define NephilimUIText_h__

#include <Nephilim/Platform.h>
#include <Nephilim/UI/UIView.h>
#include <Nephilim/Text.h>

NEPHILIM_NS_BEGIN

/**
	\class UITabView
	\brief A control that allows to display different contents according to the chosen tab
*/
class NEPHILIM_API UIText : public UIView
{
public:
	String text_string;	
	Text buttonLabel;

	bool dirty = true;

public:
	/// Set the contents of this UIText
	void setContent(const String& content);

	void updateContent();

	/// Draw the text node
	void onDraw(GraphicsDevice* graphicsDevice, const mat4& viewToWorld);
};

NEPHILIM_NS_END
#endif // NephilimUIText_h__
