#ifndef MINIMAL_BUILD

#include "Nephilim/AnimationGroupParallel.h"

PARABOLA_NAMESPACE_BEGIN

/// Update the group all at once
void AnimationGroupParallel::update(float elapsedTime){
	if(playing()){
		for(unsigned int i = 0; i < m_animables.size(); i++){
			myAnimations[i]->update(elapsedTime);
		}
	}	
};

PARABOLA_NAMESPACE_END

#endif