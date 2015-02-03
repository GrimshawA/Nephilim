#include <Nephilim/UI/UIComponentLineEdit.h>
#include <Nephilim/UI/UIView.h>

NEPHILIM_NS_BEGIN

UIComponentLineEdit::UIComponentLineEdit()
: m_pipeIndex(0)
, m_textColor(Color::Black)
, m_type(Regular)
, m_charLimit(16)
{

}

void UIComponentLineEdit::onEvent(Event event, UIView* view)
{
	if(event.type == Event::MouseButtonPressed)
	{
		vec2 mouse(event.getPointerPosition().x, event.getPointerPosition().y);
		if(mouse.x >= view->getPosition().x && mouse.y >= view->getPosition().y && mouse.x <= view->getPosition().x + view->getSize().x && mouse.y <= view->getPosition().y + view->getSize().y)
		{
			view->m_hasFocus = true;
		}
		else
		{
			view->m_hasFocus = false;
		}
	}

	if(view->m_hasFocus)
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

}


bool UIComponentLineEdit::onKeyPressed(Keyboard::Key key)
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
	else if(key == Keyboard::Return)
	{
		onReturnPressed(s);
	}

	return false;
}

bool UIComponentLineEdit::onTextEvent(Uint32 code)
{
	if(code >= 32)
	{
		addCharacter(code);
		return true;
	}
	else return false;
}


void UIComponentLineEdit::setType(UILineEditTypes type)
{
	m_type = type;
}

void UIComponentLineEdit::setCharacterLimit(std::size_t limit)
{
	m_charLimit = limit;
}

void UIComponentLineEdit::addCharacter(Uint32 charCode)
{
	if(s.length() < m_charLimit)
	{
		s.insert(s.begin() + m_pipeIndex, charCode);
		m_pipeIndex++;
	}	
}

void UIComponentLineEdit::eraseCharacter()
{
	if(s.empty())
		return;

	if(m_pipeIndex <= 0)
		return;

	s.erase(s.begin() + m_pipeIndex - 1);
	m_pipeIndex--;
}


void UIComponentLineEdit::onRender(GraphicsDevice* renderer, UIView* view)
{
	RectangleShape backgroundRect;
	backgroundRect.setColor(Color(240,240,240,240));
	backgroundRect.setRect(view->getBounds());
	renderer->draw(backgroundRect);

	if (view->getCore() && view->getCore()->m_defaultFont)
		t.setFont(*view->getCore()->m_defaultFont);

	FloatRect mRect = view->getBounds();

	if(m_type == Regular)
	{
		t.setString(s);
	}
	else
	{
		t.setString(String(s.length(), '*'));
	}
	t.setPosition(mRect.left,mRect.top);
	t.setCharacterSize(static_cast<unsigned int>(view->getSize().y * 0.9f));	
	t.setColor(m_textColor);

	renderer->draw(t);

	// The pipe
	if(view->m_hasFocus)
	{
		float pipePosition = t.getCharacterPosition(m_pipeIndex).x + 1;
		renderer->drawDebugLine(Vec2f(mRect.left + pipePosition, mRect.top), Vec2f(mRect.left + pipePosition, mRect.top + t.getCharacterSize()), Color(0,0,0,150));
	}
}
NEPHILIM_NS_END