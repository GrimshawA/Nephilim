#ifndef NephilimUIComponentDebug_h__
#define NephilimUIComponentDebug_h__

#include <Nephilim/UI/UIView.h>
#include <Nephilim/Foundation/Color.h>
#include <Nephilim/Foundation/Vector.h>

NEPHILIM_NS_BEGIN

/**
	\class UIDebugWidget
	\brief Debug utility to show some text and colors for testing purposes
*/
class NEPHILIM_API UIDebugWidget : public UIView
{
public:

	UIDebugWidget();
	UIDebugWidget(const Color& color);

	void onPropertySet(const StringList& targetObject, const String& value);

	void onAttach(UIView* view);

	void onRender(GraphicsDevice* renderer, UIView* view, const mat4& parentTransform);

	Color mColor;
};

NEPHILIM_NS_END

#endif // NephilimUIComponentDebug_h__
