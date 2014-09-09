#include <Nephilim/UI/UISoftwareKeyboard.h>
#include <Nephilim/Text.h>
#include <Nephilim/UI/UIButton.h>

#include <iostream>
using namespace std;

NEPHILIM_NS_BEGIN

/// Constructs the button
UISoftwareKeyboard::UISoftwareKeyboard() : UIView(), m_color(0,0,0) , hover(false){
	UIButton* eraseButton = new UIButton("<-");
	eraseButton->setPosition(1600, 700);
	eraseButton->setSize(200,50);
	eraseButton->onClick.connect(MAKE_SLOT_LOCAL(UISoftwareKeyboard, emitErase));
	attach(eraseButton);
};

void UISoftwareKeyboard::emitErase()
{
	onErase();
}


/// Constructs the button from a label text
UISoftwareKeyboard::UISoftwareKeyboard(const String& title) : UIView(), m_color(0,0,0), m_label(title), hover(false){

};

/// Callback to handle an event
bool UISoftwareKeyboard::onEventNotification(Event& event){
	if(event.type == Event::MouseButtonReleased){
		if(mRect.contains(event.mouseButton.x, event.mouseButton.y)){
			onClick();
		}
	}	

	if(event.type == Event::MouseMoved)
	{
		if(mRect.contains(event.mouseMove.x, event.mouseMove.y)){	
			//setProperty<Color>("background-color", Color::White);
		}
		else
		{
			//setProperty<Color>("background-color", Color(91,91,91));
		}
	}

	if(event.type == Event::TextEntered)
	{
		//onTextEntered(event.text.unicode);
	}

	return UIView::onEventNotification(event);
}

/// Callback to render itself, renders children
void UISoftwareKeyboard::draw(Renderer* renderer){

	Text t;
	t.setString(m_label);
	t.setColor(m_color);
	t.setPosition(mRect.left, mRect.top);
	renderer->draw(t);
};

NEPHILIM_NS_END
