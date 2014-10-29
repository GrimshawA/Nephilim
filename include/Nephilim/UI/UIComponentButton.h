#ifndef NephilimUIComponentButton_h__
#define NephilimUIComponentButton_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Strings.h>
#include <Nephilim/UI/UIComponent.h>
#include <Nephilim/Color.h>
#include <Nephilim/Texture.h>

NEPHILIM_NS_BEGIN

class NEPHILIM_API UIComponentButton : public UIComponent
{
public:
	UIComponentButton();

	/// Default construction with a text
	UIComponentButton(const String& text);

	void onAttach(UIView* view);

	void onEvent(Event event, UIView* view);

	void onRender(GraphicsDevice* renderer, UIView* view, const mat4& parentTransform);

	void onPropertySet(const StringList& targetObject, const String& value);

	void refreshTextures();

	bool hovering;

	String mString;

	Color mNormalColor;
	Color mHoverColor;

	String mHoverTextureSource;
	String mNormalTextureSource;

	Texture* mTexture;
	Texture* mHoverTexture;
};

NEPHILIM_NS_END
#endif // NephilimUIComponentButton_h__
