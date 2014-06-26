#ifndef NephilimUIComponentDebug_h__
#define NephilimUIComponentDebug_h__

#include <Nephilim/Platform.h>
#include <Nephilim/UIComponent.h>
#include <Nephilim/Color.h>
#include <Nephilim/Vectors.h>

NEPHILIM_NS_BEGIN

class UIView;

class NEPHILIM_API UIComponentDebugColor : public UIComponent
{
public:

	UIComponentDebugColor();
	UIComponentDebugColor(const Color& color);

	void onPropertySet(const StringList& targetObject, const String& value);

	void onAttach(UIView* view);

	void onRender(Renderer* renderer, UIView* view);

	Color mColor;
};

NEPHILIM_NS_END

#endif // NephilimUIComponentDebug_h__
