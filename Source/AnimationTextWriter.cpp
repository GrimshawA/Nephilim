#include "Nephilim/AnimationTextWriter.h"
#include <iostream>

#include <cmath>

PARABOLA_NAMESPACE_BEGIN

/// Default construction
AnimationTextWriter::AnimationTextWriter(){
	myTotalTime = 0.f;
	prevIndex = -1;
	myFunction = new AnimationEasingQuad();
};

/// Set the destination text for the animation
void AnimationTextWriter::setText(const String &text){
	myText = text;
};

/// Set the duration of the writing
void AnimationTextWriter::setDuration(float duration){
	myDuration = duration;
};

/// Update state of the animation
void AnimationTextWriter::update(float elapsedTime){
	if(playing()){
		myTotalTime += elapsedTime;
		if(myTotalTime >= myDuration){		
			stop();
		}
		else{
			float current_index = myFunction->compute(myTotalTime, 0.f, (float)myText.length(), myDuration);
			//std::cout<<"computed: "<<current_index<<std::endl;
			if( floor(current_index) > prevIndex && current_index >= 0 && current_index < myText.length()){
				// shout any in between characters
				if(prevIndex + 1 < floor(current_index)){
					// some characters missing
					for(int pos = prevIndex + 1; pos < floor(current_index); pos++){
						m_animables[0]->animable_add_character(myText[pos]);
					}
					
				}
				m_animables[0]->animable_add_character(myText[current_index]);
				prevIndex = floor(current_index);
			}
		}
	}
};

/// Play override
void AnimationTextWriter::play(){
	myTotalTime = 0.f;
	prevIndex = -1;
	AnimationInterface::play();
};

PARABOLA_NAMESPACE_END
