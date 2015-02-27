#ifndef NephilimUIComponentImage_h__
#define NephilimUIComponentImage_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Foundation/String.h>
#include <Nephilim/UI/UIComponent.h>
#include <Nephilim/Graphics/Text.h>


NEPHILIM_NS_BEGIN



class NEPHILIM_API UIComponentImage : public UIComponent
{
public:
	UIComponentImage();

	UIComponentImage(const String& src); /// Load from an image

	void onAttach(UIView* view);

	void onRender(GraphicsDevice* renderer, UIView* view, const mat4& parentTransform);

	void onPropertySet(const StringList& targetObject, const String& value);

	void refreshTextureHandle();

	Texture2D* mTexture;
	String mSourceTexture;
};

NEPHILIM_NS_END
#endif // NephilimUIComponentImage_h__
