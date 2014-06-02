#include <Nephilim/UI/UIComponentImage.h>
#include <Nephilim/UIView.h>
#include <Nephilim/StringList.h>
#include <Nephilim/ContentBank.h>

NEPHILIM_NS_BEGIN

UIComponentImage::UIComponentImage()
: UIViewComponent()
, mTexture(NULL)
{

}


UIComponentImage::UIComponentImage(const String& src)
: UIViewComponent()
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
				//Log("IMAGE IMAGE IMAGE HAS NOW A TEXTURE");
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