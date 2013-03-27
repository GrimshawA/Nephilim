#include <Nephilim/UIProgressBar.h>
#include <Nephilim/Text.h>

#include <iostream>
using namespace std;

PARABOLA_NAMESPACE_BEGIN

/// Constructs the progress bar with default values
UIProgressBar::UIProgressBar() : m_currentValue(0){

};

/// Constructs the progress bar with defined values
UIProgressBar::UIProgressBar(int maxValue, const String& message) : m_currentValue(0){
	m_rect.set(300,300,300,70);
};

/// Callback to render itself
void UIProgressBar::draw(Renderer* renderer){
	
	renderer->drawDebugQuad(m_rect.left + m_rect.width/2,m_rect.top + 14,0,m_currentValue, 20, Color::Red);

	Text message;
	message.setString("Loading...");
	message.setPosition(m_rect.left, m_rect.top + 32);
	message.setCharacterSize(10);
	renderer->draw(message);
};

bool UIProgressBar::onEventNotification(Event& event){
	if(event.type == Event::KeyPressed){
		cout<<"growing bar"<<endl;
		m_currentValue += 5;
	}

	return true;
};

PARABOLA_NAMESPACE_END