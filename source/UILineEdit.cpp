#include <Nephilim/UILineEdit.h>


#include <iostream>
using namespace std;


NEPHILIM_NS_BEGIN

UILineEdit::UILineEdit() : UIControl(), m_pipeIndex(0)
{

}


bool UILineEdit::onEventNotification(Event& event){
	/*if(event.type == Event::TextEntered){
		s += event.text.unicode;
		t.setString(s);
	}*/
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


void UILineEdit::addCharacter(Uint32 charCode)
{
	s.insert(s.begin() + m_pipeIndex, charCode);
	m_pipeIndex++;
}

void UILineEdit::eraseCharacter()
{
	s.erase(s.begin() + m_pipeIndex - 1);
	m_pipeIndex--;
}

void UILineEdit::setText(const String& text){
	s = text;
	t.setString(s);
};


void UILineEdit::draw(Renderer* renderer){
	t.setString(s);
	t.setPosition(m_bounds.left,m_bounds.top);
	t.setCharacterSize(15);
	if(m_hasFocus)
	{
		t.setColor(Color::Red);
	}
	else
	{
		t.setColor(Color::White);
	}
	
	// The pipe
	float pipePosition = t.getCharacterPosition(m_pipeIndex).x + 1;
	renderer->draw(t);
	renderer->drawDebugLine(Vec2f(m_bounds.left + pipePosition, m_bounds.top), Vec2f(m_bounds.left + pipePosition, m_bounds.top + t.getCharacterSize()), Color::Red);

	//renderer->drawDebugLine(Vec2f(0,0), Vec2f(400,400), Color::White);
};


NEPHILIM_NS_END