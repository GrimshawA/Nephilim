#ifndef NephilimUIComponentButton_h__
#define NephilimUIComponentButton_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Strings.h>
#include <Nephilim/UIComponent.h>
#include <Nephilim/Color.h>

NEPHILIM_NS_BEGIN

class NEPHILIM_API UIComponentButton : public UIViewComponent
{
public:
	UIComponentButton();

	void onAttach(UIView* view);

	void onEvent(Event event, UIView* view);

	void onRender(Renderer* renderer, UIView* view);

	void onPropertySet(const StringList& targetObject, const String& value);

	bool hovering;

	String mString;
	Color mNormalColor;
};

NEPHILIM_NS_END
#endif // NephilimUIComponentButton_h__
