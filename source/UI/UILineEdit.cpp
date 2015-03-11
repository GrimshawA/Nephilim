#include <Nephilim/UI/UILineEdit.h>

NEPHILIM_NS_BEGIN

UILineEdit::UILineEdit()
: Widget()
, m_pipeIndex(0)
, m_textColor(Color::Black)
, m_type(Regular)
, m_charLimit(16)
{
	setSize(300.f, 60.f);
}

/// Constructs directly into a parent container
UILineEdit::UILineEdit(Widget* ParentView)
: Widget()
, m_pipeIndex(0)
, m_textColor(Color::Black)
, m_type(Regular)
, m_charLimit(16)
{
	ParentView->attach(this);
	setSize(300.f, 60.f);
}

/// Clear the contents
void UILineEdit::clear()
{
	m_pipeIndex = 0;
	StringBuffer.clear();
}

/// Called on the subclass to have it paint its contents
void UILineEdit::onPaint(UIPainter& painter)
{
	painter.drawRect(getRect());
	painter.drawText(getGlobalRect(), PainterFlags::AlignCenterH | PainterFlags::AlignCenterV, StringBuffer);
}

/// Called when an event arrives at this widget
void UILineEdit::event(UxEvent* event)
{

}

/// Called when an event arrives at this widget
void UILineEdit::keyPressEvent(UxKeyEvent* key)
{
	if (key->unicode)
	{
		addCharacter(key->unicode);
	}
	else if (key->key == Keyboard::Back)
	{
		eraseCharacter();
	}
}

void UILineEdit::setTextColor(const Color& color)
{
	m_textColor = color;
}

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

void UILineEdit::setCharacterLimit(std::size_t limit)
{
	m_charLimit = limit;
}

void UILineEdit::addCharacter(Uint32 charCode)
{
	if(StringBuffer.length() < m_charLimit)
	{
		StringBuffer.insert(StringBuffer.begin() + m_pipeIndex, charCode);
		m_pipeIndex++;
	}
}

void UILineEdit::eraseCharacter()
{
	if(!StringBuffer.empty())
	{
		StringBuffer.erase(StringBuffer.begin() + m_pipeIndex - 1);
		m_pipeIndex--;
	}
}

void UILineEdit::setText(const String& text)
{
	StringBuffer = text;
	t.setString(StringBuffer);
}

void UILineEdit::setType(UILineEditTypes type)
{
	m_type = type;
}

NEPHILIM_NS_END