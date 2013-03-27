#include <Nephilim/UIConsole.h>
#include <Nephilim/Text.h>

PARABOLA_NAMESPACE_BEGIN

/// Callback to render itself
void UIConsole::draw(Renderer* renderer){
	Text te;
	te.setCharacterSize(10);
	te.setString(m_input);
	te.setPosition(m_bounds.left, m_bounds.top);
	renderer->draw(te);
}

bool UIConsole::onEventNotification(Event& event){
	if(event.type == Event::KeyPressed && event.key.code == Keyboard::Return){
		if(!m_input.empty()){
			onCommandSubmitted.emit(m_input);
			m_input.clear();
		}
	}
	else if(event.type == Event::TextEntered && event.text.unicode >= 32){
		m_input += event.text.unicode;
	}

	return false;
};

PARABOLA_NAMESPACE_END