#ifndef NephilimUIComponentButton_h__
#define NephilimUIComponentButton_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Strings.h>
#include <Nephilim/UIComponent.h>
#include <Nephilim/Color.h>
#include <Nephilim/Texture.h>

NEPHILIM_NS_BEGIN

class NEPHILIM_API UIComponentButton : public UIViewComponent
{
public:
	UIComponentButton();

	void onAttach(UIView* view);

	void onEvent(Event event, UIView* view);

	void onRender(Renderer* renderer, UIView* view);

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
