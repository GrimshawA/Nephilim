#include <Nephilim/UI/UISlider.h>

#include <iostream>
using namespace std;

NEPHILIM_NS_BEGIN

/// Constructs the slider with default values
UISlider::UISlider(){
	mRect.set(0,0, 800, 200);

//	m_sliderRect.set(m_rect.left + 10, m_rect.top + m_rect.height/2,40,40);
	dragging = false;
	m_maxValue = 255;

	adjustPositions();
};

/// Adjust the internal positions of objects according to bounds
void UISlider::adjustPositions(){
	m_draggableArea.set(0, 0,mRect.width*0.7, 40);
	m_draggableArea.setCenter(mRect.left + mRect.width/2,mRect.top + mRect.height/2 );

	m_sliderRect.set(0,0,40,40);
	m_sliderRect.setPosition(m_draggableArea.left, m_draggableArea.top);
};

/// Callback to render itself
void UISlider::draw(Renderer* renderer){
	
	renderer->drawDebugQuad(m_draggableArea.left + m_draggableArea.width/2, m_draggableArea.top + m_draggableArea.height/2, 0,m_draggableArea.width, m_draggableArea.height, Color(200,200,190) );

	renderer->drawDebugQuad(m_sliderRect.left + m_sliderRect.width/2, m_sliderRect.top + m_sliderRect.height/2, 0, m_sliderRect.width, m_sliderRect.height, Color::Red );
	
};

/// Callback when the position of the control changed, for updating nested objects
void UISlider::onPositionChanged(){
	adjustPositions();
};

/// Sets the value of the slider knob
void UISlider::setValue(int value){
	m_sliderRect.setPosition(m_draggableArea.left + value, m_sliderRect.top);
};


/// Callback to handle an event
bool UISlider::onEventNotification(Event& event){
	if(event.type == Event::MouseButtonPressed){
		// check boundaries
		if(m_sliderRect.contains(event.mouseButton.x, event.mouseButton.y)){
			dragging = true;
		}
	}
	else if(event.type == Event::MouseMoved){
		if(dragging){
			Vec2f mouse = Vec2f(event.mouseMove.x, event.mouseMove.y);
			if(m_draggableArea.contains(mouse.x, mouse.y)){
				m_sliderRect.setPosition(mouse.x, m_sliderRect.top);
			}
			float factor = (mouse.x - m_draggableArea.left)/m_draggableArea.width;
			onValueChanged((float)m_maxValue * factor);
		}		
	}
	else if(event.type == Event::MouseButtonReleased){
		dragging = false;
	}

	return true;
};

NEPHILIM_NS_END