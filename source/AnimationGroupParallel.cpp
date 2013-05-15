#ifndef MINIMAL_BUILD

#include "Nephilim/AnimationGroupParallel.h"

NEPHILIM_NS_BEGIN

/// Update the group all at once
void AnimationGroupParallel::update(float elapsedTime){
	if(playing()){
		for(unsigned int i = 0; i < m_animables.size(); i++){
			myAnimations[i]->update(elapsedTime);
		}
	}	
};

NEPHILIM_NS_END

#endif