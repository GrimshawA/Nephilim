#include <Nephilim/UI/UIComponentImage.h>
#include <Nephilim/UI/UIView.h>
#include <Nephilim/StringList.h>
#include <Nephilim/ContentManager.h>

NEPHILIM_NS_BEGIN

UIComponentImage::UIComponentImage()
: UIComponent()
, mTexture(NULL)
{

}


UIComponentImage::UIComponentImage(const String& src)
: UIComponent()
, mTexture(NULL)
{
	mSourceTexture = src;
}

void UIComponentImage::onAttach(UIView* view)
{
	refreshTextureHandle(); // Might need to be updated
}

void UIComponentImage::refreshTextureHandle()
{
	if(mSourceTexture.empty())
		return;

	if(mParent)
	{
		if(mParent->getContext()->content)
		{
			if(mParent->getContext()->content->load(mSourceTexture))
			{
				mTexture = mParent->getContext()->content->mGroups[""]->mTextures[mSourceTexture];
			}
			else
			{
				mTexture = NULL;
			}
		}
	}
}


void UIComponentImage::onPropertySet(const StringList& targetObject, const String& value)
{
	if(targetObject.size() == 2 && targetObject[0] == "image" && targetObject[1] == "src")
	{
		mSourceTexture = value;
		refreshTextureHandle();
	}
}

void UIComponentImage::onRender(Renderer* renderer, UIView* view)
{
	RectangleShape backgroundRect;
	backgroundRect.setRect(view->getBounds());
	if(mTexture) backgroundRect.setTexture(mTexture);
	renderer->draw(backgroundRect);
}

NEPHILIM_NS_END