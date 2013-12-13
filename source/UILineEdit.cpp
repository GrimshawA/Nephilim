#include <Nephilim/UILineEdit.h>


#include <iostream>
using namespace std;


NEPHILIM_NS_BEGIN

UILineEdit::UILineEdit()
: UIView()
, m_pipeIndex(0)
, m_textColor(Color::Black)
, m_type(Regular)
, m_charLimit(16)

{

}

void UILineEdit::setTextColor(const Color& color)
{
	m_textColor = color;
}


bool UILineEdit::onEventNotification(Event& event)
{
	if(event.type == Event::MouseButtonPressed)
	{
		vec2 mouse(event.getPointerPosition().x, event.getPointerPosition().y);
		if(mouse.x >= getPosition().x && mouse.y >= getPosition().y && mouse.x <= getPosition().x + getSize().x && mouse.y <= getPosition().y + getSize().y)
		{
			m_hasFocus = true;
		}
		else
		{
			m_hasFocus = false;
		}
	}

	if(m_hasFocus)
	{
		if(event.type == Event::TextEntered)
		{
			onTextEvent(event.text.unicode);
		}

		if(event.type == Event::KeyPressed)
		{
			onKeyPressed(event.key.code);
		}
	}	

	return true;
};

bool UILineEdit::onKeyPressed(Keyboard::Key key)
{
	if(key == Keyboard::Left)
	{
		m_pipeIndex--;
	}
	else if(key == Keyboard::Right)
	{
		m_pipeIndex++;
	}
	else if(key == Keyboard::Back)
	{
		eraseCharacter();
	}
	else if(key == Keyboard::Delete)
	{
		m_pipeIndex++;
		eraseCharacter();
	}

	return false;
}

bool UILineEdit::onTextEvent(Uint32 code)
{
	if(code >= 32)
	{
		addCharacter(code);
		return true;
	}
	else return false;
}

void UILineEdit::setCharacterLimit(size_t limit)
{
	m_charLimit = limit;
}


void UILineEdit::addCharacter(Uint32 charCode)
{
	if(s.length() < m_charLimit)
	{
		s.insert(s.begin() + m_pipeIndex, charCode);
		m_pipeIndex++;
	}	
}

void UILineEdit::eraseCharacter()
{
	if(!s.empty())
	{
		s.erase(s.begin() + m_pipeIndex - 1);
		m_pipeIndex--;
	}
}

void UILineEdit::setText(const String& text){
	s = text;
	t.setString(s);
};

void UILineEdit::setType(UILineEditTypes type)
{
	m_type = type;
}


void UILineEdit::draw(Renderer* renderer)
{
	if(getContext() && getContext()->m_defaultFont)
		t.setFont(*getContext()->m_defaultFont);

	if(m_type == Regular)
	{
		t.setString(s);
	}
	else
	{
		t.setString(String(s.length(), '*'));
	}
	t.setPosition(mRect.left,mRect.top);
	t.setCharacterSize(static_cast<unsigned int>(getSize().y * 0.9f));	
	t.setColor(m_textColor);

	renderer->draw(t);

	// The pipe
	if(m_hasFocus)
	{
		float pipePosition = t.getCharacterPosition(m_pipeIndex).x + 1;
		renderer->drawDebugLine(Vec2f(mRect.left + pipePosition, mRect.top), Vec2f(mRect.left + pipePosition, mRect.top + t.getCharacterSize()), Color(0,0,0,150));
	}
};


NEPHILIM_NS_END