#ifndef PARABOLA_ANIMATIONGROUP_H
#define PARABOLA_ANIMATIONGROUP_H

#include "Platform.h"
#include "Animation.h"
#include <vector>

PARABOLA_NAMESPACE_BEGIN
/**
	\ingroup Animation
	\class AnimationGroup
	\brief Base grouping class for animations
*/
class PARABOLA_API AnimationGroup : public AnimationInterface{
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

PARABOLA_NAMESPACE_END
#endif