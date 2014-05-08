#include <Nephilim/UI/UIComponentButton.h>
#include <Nephilim/UIView.h>
#include <Nephilim/Text.h>
#include <Nephilim/StringList.h>
#include <Nephilim/ContentBank.h>

NEPHILIM_NS_BEGIN

UIComponentButton::UIComponentButton()
: UIViewComponent()
, mString("Button")
, mTexture(NULL)
, mHoverTexture(NULL)
{
	mNormalColor = Color::Black;
	mHoverColor = Color::Yellow;
}

void UIComponentButton::onPropertySet(const StringList& targetObject, const String& value)
{
	if(targetObject.size() == 2 && targetObject[0] == "button" && targetObject[1] == "caption")
	{
		mString = value;
	}

	if(targetObject.size() == 2 && targetObject[0] == "button" && targetObject[1] == "color")
	{
		if(value == "red")
		{
			mNormalColor = Color::Red;
		}
	}

	if(targetObject.size() == 2 && targetObject[0] == "button" && targetObject[1] == "texture")
	{
		mNormalColor = Color::White;
		mNormalTextureSource = value;

		refreshTextures();
	}

	if(targetObject.size() == 2 && targetObject[0] == "button" && targetObject[1] == "htexture")
	{
		mHoverColor = Color::White;
		mHoverTextureSource = value;

		refreshTextures();
	}
}

void UIComponentButton::refreshTextures()
{
	if(mParent)
	{
		if(mParent->getContext()->content)
		{
			mTexture = mParent->getContext()->content->getTexture(mNormalTextureSource);
			if(!mTexture)
			{
				mParent->getContext()->content->load(mNormalTextureSource);
				mTexture = mParent->getContext()->content->getTexture(mNormalTextureSource);
			}

			mHoverTexture = mParent->getContext()->content->getTexture(mHoverTextureSource);
			if(!mHoverTexture)
			{
				mParent->getContext()->content->load(mHoverTextureSource);
				mHoverTexture = mParent->getContext()->content->getTexture(mHoverTextureSource);
			}
		}
	}
}

void UIComponentButton::onAttach(UIView* view)
{
	hovering = false;
}

void UIComponentButton::onEvent(Event event, UIView* view)
{
	if(event.isPointerMoved())
	{
		hovering = view->getBounds().contains(event.getPointerPosition().x, event.getPointerPosition().y);
	}
}

void UIComponentButton::onRender(Renderer* renderer, UIView* view)
{
	if(hovering)
	{
		RectangleShape hoverRect;
		hoverRect.setRect(view->getBounds());
		hoverRect.setColor(mHoverColor);
		if(mTexture)
		{
			hoverRect.setTexture(mHoverTexture);
		}
		renderer->draw(hoverRect);
	}
	else
	{
		RectangleShape hoverRect;
		hoverRect.setRect(view->getBounds());
		hoverRect.setColor(mNormalColor);
		if(mTexture)
		{
			hoverRect.setTexture(mTexture);
		}
		renderer->draw(hoverRect);
	}

	// -- Label
	Text buttonLabel;
	buttonLabel.setFont(*view->mCore->m_defaultFont);
	buttonLabel.setString(mString);
	buttonLabel.setCharacterSize(view->mRect.height / 2);
	buttonLabel.setOrigin(static_cast<int>((buttonLabel.getLocalBounds().width / 2.f ) + 0.5f), static_cast<int>((buttonLabel.getLocalBounds().height / 2.f) + 0.5f));
	buttonLabel.setPosition(static_cast<int>((view->mRect.left + view->mRect.width / 2.f ) + 0.5f), static_cast<int>((view->mRect.top +  view->mRect.height / 2.f) + 0.5f));
	if(buttonLabel.getLocalBounds().width > view->getSize().x * 0.9f)
	{
		// The text is too big and passes the 90% of the button's width
		float diminishRatio = (view->getSize().x * 0.9f) / buttonLabel.getLocalBounds().width;
		buttonLabel.setCharacterSize(static_cast<unsigned int>(static_cast<float>(buttonLabel.getCharacterSize()) * diminishRatio));
		buttonLabel.setOrigin(static_cast<int>((buttonLabel.getLocalBounds().width / 2.f ) + 0.5f), static_cast<int>((buttonLabel.getLocalBounds().height / 2.f) + 0.5f));
	}
	renderer->draw(buttonLabel);
}

NEPHILIM_NS_END