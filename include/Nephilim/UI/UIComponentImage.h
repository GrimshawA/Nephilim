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
	UIComponentImage();

	UIComponentImage(const String& src); /// Load from an image

	void onAttach(UIView* view);

	void onRender(Renderer* renderer, UIView* view);

	void onPropertySet(const StringList& targetObject, const String& value);

	void refreshTextureHandle();

	Texture* mTexture;
	String mSourceTexture;
};

NEPHILIM_NS_END
#endif // NephilimUIComponentImage_h__
