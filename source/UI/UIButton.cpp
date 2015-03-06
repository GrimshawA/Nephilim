#include <Nephilim/UI/UIButton.h>
#include <Nephilim/Graphics/Text.h>
#include <Nephilim/Graphics/RectangleShape.h>

#include <iostream>
using namespace std;

NEPHILIM_NS_BEGIN


UIButton::UIButton()
: UIView()
, m_color(0,0,0)
, m_label("")
, hover(false)
, m_normalTexture(NULL)
{
	UIPropertyMap& hoverproperties = m_styleInfo["hover"];
	hoverproperties["color"] = UIProperty(Color::Blue);

	UIPropertyMap& normalproperties = m_styleInfo["normal"];
	normalproperties["color"] = UIProperty(Color::Orange);

	hoverproperties["text-color"] = UIProperty(Color::Black);
	normalproperties["text-color"] = UIProperty(Color::Black);
}

UIButton::UIButton(const String& title)
: UIView()
, m_color(0,0,0)
, m_label(title)
, hover(false)
, m_normalTexture(NULL)
{
	UIPropertyMap& hoverproperties = m_styleInfo["hover"];
	hoverproperties["color"] = UIProperty(Color::Blue);

	UIPropertyMap& normalproperties = m_styleInfo["normal"];
	normalproperties["color"] = UIProperty(Color::Orange);

	hoverproperties["text-color"] = UIProperty(Color::Black);
	normalproperties["text-color"] = UIProperty(Color::Black);
}

/// Constructs a button with a given text directly at a given position
UIButton::UIButton(const String& content, const FloatRect& rect)
: UIView()
, m_color(0,0,0)
, m_label(content)
, hover(false)
, m_normalTexture(NULL)
{
	setRect(rect);

	UIPropertyMap& hoverproperties = m_styleInfo["hover"];
	hoverproperties["color"] = UIProperty(Color::Blue);

	UIPropertyMap& normalproperties = m_styleInfo["normal"];
	normalproperties["color"] = UIProperty(Color::Orange);

	hoverproperties["text-color"] = UIProperty(Color::Black);
	normalproperties["text-color"] = UIProperty(Color::Black);
}

/// Destructor
UIButton::~UIButton(){}


void UIButton::setNormalTexture(const String& filename)
{
	
}

void UIButton::setHoverTexture(const String& filename)
{
	
}

bool UIButton::onEventNotification(Event& event)
{
	

	return true;
}

UIView* UIButton::clone()
{
	return new UIButton(*this);
};

void UIButton::innerLanguageSwitch()
{
/*	String res =  mCore->m_localization.getString(m_baseLabel);
	if(!res.empty())m_label = res;*/
}

void UIButton::setRawProperty(const String& name, const String& val)
{
	if(name == "background-image")
	{
		cout<<"[UIButton] Assigning image"<<endl;
	}
}

/// Sets the label of the button
void UIButton::setLabel(const String& text)
{
	m_label = text;
	m_baseLabel = m_label;
}

String UIButton::getLabel()
{
	return m_label;
}

UIButton::TextureInfo& UIButton::getStateTextureInfo(UIButtonState state)
{
	std::map<UIButtonState, TextureInfo>::iterator it = stateTextures.find(state);

	// This state wasn't created yet, no texture assigned
	if(it == stateTextures.end())
	{
		stateTextures[state].texture = NULL;
		return stateTextures[state];
	}
	else
	{
		// In case we have a texture assigned but the rect is invalid, make it use the whole texture
		if((*it).second.texture && ((*it).second.rect.width == 0.f || (*it).second.rect.height == 0.f))
		{
			(*it).second.rect = FloatRect(0.f, 0.f, (*it).second.texture->getSize().x, (*it).second.texture->getSize().y);
		}
		return (*it).second;
	}
}


/// Called on the subclass to have it paint its contents
void UIButton::onPaint(UIPainter& painter)
{
	GraphicsDevice* renderer = painter.graphicsDevice;

	RectangleShape c(getRect(), Color::Yellow);
	//renderer->draw(c);

	if(_core->m_defaultFont && !_core->m_defaultFont->isLoaded())
	{
		Log("UI: There is no default font for showing text.");
	}

	backgroundShape.setPosition(getPosition());
	backgroundShape.setSize(getSize());
	if(m_classInfo["hover"])
	{
		buttonLabel.setColor(m_styleInfo["hover"]["text-color"].getColor());
		backgroundShape.setColor(m_styleInfo["hover"]["color"].getColor());
		backgroundShape.setTextureRect(hover_texture_rect);

		TextureInfo texInfo = getStateTextureInfo(Hovered);
		if(texInfo.texture)
		{
			backgroundShape.setTexture(texInfo.texture);
			backgroundShape.setTextureRect(texInfo.rect);
		}
	}
	else
	{
		buttonLabel.setColor(m_styleInfo["normal"]["text-color"].getColor());
		backgroundShape.setColor(m_styleInfo["normal"]["color"].getColor());
		backgroundShape.setTextureRect(normal_texture_rect);

		TextureInfo texInfo = getStateTextureInfo(Regular);
		if(texInfo.texture)
		{
			backgroundShape.setTexture(texInfo.texture);
			backgroundShape.setTextureRect(texInfo.rect);
		}
	}

	renderer->draw(backgroundShape);
	
    // -- Label
	//buttonLabel.setFont(*_core->m_defaultFont);
	buttonLabel.setString(m_label);
//	buttonLabel.setCharacterSize(mRect.height / 2);
	buttonLabel.setOrigin(static_cast<int>((buttonLabel.getLocalBounds().width / 2.f ) + 0.5f), static_cast<int>((buttonLabel.getLocalBounds().height / 2.f) + 0.5f));
	//buttonLabel.setPosition(static_cast<int>((mRect.left + mRect.width / 2.f ) + 0.5f), static_cast<int>((mRect.top +  mRect.height / 2.f) + 0.5f));
	if(buttonLabel.getLocalBounds().width > getSize().x * 0.9f)
	{
		// The text is too big and passes the 90% of the button's width
		float diminishRatio = (getSize().x * 0.9f) / buttonLabel.getLocalBounds().width;
		buttonLabel.setCharacterSize(static_cast<unsigned int>(static_cast<float>(buttonLabel.getCharacterSize()) * diminishRatio));
		buttonLabel.setOrigin(static_cast<int>((buttonLabel.getLocalBounds().width / 2.f ) + 0.5f), static_cast<int>((buttonLabel.getLocalBounds().height / 2.f) + 0.5f));
	}
	renderer->draw(buttonLabel);
};

NEPHILIM_NS_END
