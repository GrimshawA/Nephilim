#include "Nephilim/AnimationFactory.h"
#include "Nephilim/AnimationPosition.h"
#include "Nephilim/AnimationDimension.h"

#include <iostream>
using namespace std;

NEPHILIM_NS_BEGIN

void AnimationFactory::addAnimation(AnimationInterface* animation){
		myAnimations.push_back(animation);
		animation->play();
}

/// Update the state of associated animations
void AnimationFactory::update(float elapsedTime){
	for(std::vector<AnimationInterface*>::iterator it = myAnimations.begin(); it != myAnimations.end(); it++){
		(*it)->update(elapsedTime);
		//cout<<"Updating the animations.."<<endl;
	}
};

NEPHILIM_NS_END
