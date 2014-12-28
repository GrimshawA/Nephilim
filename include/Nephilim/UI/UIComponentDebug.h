#ifndef NephilimUIComponentDebug_h__
#define NephilimUIComponentDebug_h__

#include <Nephilim/Platform.h>
#include <Nephilim/UI/UIComponent.h>
#include <Nephilim/Color.h>
#include <Nephilim/Math/Vectors.h>

NEPHILIM_NS_BEGIN

class UIView;

class NEPHILIM_API UIComponentDebugColor : public UIComponent
{
public:

	UIComponentDebugColor();
	UIComponentDebugColor(const Color& color);

	void onPropertySet(const StringList& targetObject, const String& value);

	void onAttach(UIView* view);

	void onRender(GraphicsDevice* renderer, UIView* view, const mat4& parentTransform);

	Color mColor;
};

NEPHILIM_NS_END

#endif // NephilimUIComponentDebug_h__
