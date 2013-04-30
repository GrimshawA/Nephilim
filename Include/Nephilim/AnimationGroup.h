#ifndef PARABOLA_ANIMATIONGROUP_H
#define PARABOLA_ANIMATIONGROUP_H

#include "Platform.h"
#include "AnimationInterface.h"
#include <vector>

NEPHILIM_NS_BEGIN
/**
	\ingroup Animation
	\class AnimationGroup
	\brief Base grouping class for animations
*/
class NEPHILIM_API AnimationGroup : public AnimationInterface{
public:
	AnimationGroup() : AnimationInterface(){}

	/// Adds a new animation to the end of the list, it is deleted once it is done
	void addAnimation(AnimationInterface* animation){
		m_animations.push_back(animation);
	}


protected:
	/// The collection of animations for this group
	std::vector<AnimationInterface*> m_animations;
};

NEPHILIM_NS_END
#endif