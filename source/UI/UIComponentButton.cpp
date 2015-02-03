#include <Nephilim/UI/UIComponentButton.h>
#include <Nephilim/UI/UIView.h>
#include <Nephilim/Graphics/Text.h>
#include <Nephilim/Foundation/StringList.h>
#include <Nephilim/Game/GameContent.h>
#include <Nephilim/Foundation/Math.h>

NEPHILIM_NS_BEGIN

UIComponentButton::UIComponentButton()
: UIComponent()
, mString("Button")
, mTexture(NULL)
, mHoverTexture(NULL)
{
	mNormalColor = Color::Black;
	mHoverColor = Color::Yellow;
}

/// Default construction with a text
UIComponentButton::UIComponentButton(const String& text)
: UIComponent()
, mString(text)
, mTexture(NULL)
, mHoverTexture(NULL)
{
	mNormalColor = Color::Black;
	mHoverColor = Color::Yellow;
	mNormalColor = Color::Transparent;

}

/// Called to refresh the component
void UIComponentButton::updateStyles()
{
	Log("BUTTON UPDATING STYLES!!!!!!!!!!!!!!!!");

	StyleSheet& stylesheet = mParent->getCore()->stylesheet;

	StyleSheet::StyleArray& styles = stylesheet.getRule("button");
	StyleSheet::StyleArray& hstyles = stylesheet.getRule("button:hover");
	mNormalColor = styles.getEntry("background").toColor();
	mHoverColor = hstyles.getEntry("background").toColor();
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
		if(mParent->getCore()->content)
		{
			mTexture = mParent->getCore()->content->getTexture(mNormalTextureSource);
			if(!mTexture)
			{
				mParent->getCore()->content->load(mNormalTextureSource);
				mTexture = mParent->getCore()->content->getTexture(mNormalTextureSource);
			}

			mHoverTexture = mParent->getCore()->content->getTexture(mHoverTextureSource);
			if(!mHoverTexture)
			{
				mParent->getCore()->content->load(mHoverTextureSource);
				mHoverTexture = mParent->getCore()->content->getTexture(mHoverTextureSource);
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

void UIComponentButton::onRender(GraphicsDevice* renderer, UIView* view, const mat4& parentTransform)
{
	if(view->m_hovered)
	{
		RectangleShape hoverRect;
		hoverRect.setRect(view->getBounds());
		hoverRect.setColor(mHoverColor);
		if (mHoverTexture)
		{
			hoverRect.setTexture(mHoverTexture);
		}
		else if (!mHoverTextureSource.empty())
		{
			// let's try to get the thing
			mHoverTexture = new Texture();
			if (mHoverTexture->loadFromFile(mHoverTextureSource))
				Log("LOADED THE THING");

			hoverRect.setTexture(mHoverTexture);

		}
		hoverRect.useOwnTransform = false;
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
		else if (!mNormalTextureSource.empty())
		{
			// let's try to get the thing
			mTexture = new Texture();
			if(mTexture->loadFromFile(mNormalTextureSource))
				Log("LOADED THE THING");

			hoverRect.setTexture(mTexture);

		}
		hoverRect.useOwnTransform = false;
		renderer->draw(hoverRect);
	}

	renderer->setModelMatrix(mat4::identity);

	// -- Label
	Text buttonLabel;
	buttonLabel.setFont(*view->_core->m_defaultFont);
	buttonLabel.setString(mString);
	buttonLabel.setCharacterSize(view->mRect.height / 2);
	buttonLabel.setOrigin(static_cast<int>((buttonLabel.getLocalBounds().width / 2.f ) + 0.5f), static_cast<int>((buttonLabel.getLocalBounds().height / 2.f) + 0.5f));
	buttonLabel.setPosition(static_cast<int>((view->mRect.left + view->mRect.width / 2.f ) + 0.5f), static_cast<int>((view->mRect.top +  view->mRect.height / 2.f) + 0.5f));
	buttonLabel.setColor(Color::White);
	buttonLabel.useOwnTransform = false;
	if(buttonLabel.getLocalBounds().width > view->getSize().x * 0.9f)
	{
		// The text is too big and passes the 90% of the button's width
		float diminishRatio = (view->getSize().x * 0.9f) / buttonLabel.getLocalBounds().width;
		buttonLabel.setCharacterSize(static_cast<unsigned int>(static_cast<float>(buttonLabel.getCharacterSize()) * diminishRatio));
		buttonLabel.setOrigin(static_cast<int>((buttonLabel.getLocalBounds().width / 2.f ) + 0.5f), static_cast<int>((buttonLabel.getLocalBounds().height / 2.f) + 0.5f));
	}
	mat4 localTransform = mat4::translate(vec3(0.f, 20.f, 1.f)) * mat4::rotatex(math::pi);

	renderer->setModelMatrix(parentTransform);
	renderer->draw(buttonLabel);
	//renderer->setModelMatrix(mat4::identity);
	//Log("Drawing button text: %s", mString.c_str());
}

NEPHILIM_NS_END