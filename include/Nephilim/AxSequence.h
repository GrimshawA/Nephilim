#ifndef NephilimAxSequence_h__
#define NephilimAxSequence_h__

#include "Platform.h"
#include "AnimationGroup.h"

NEPHILIM_NS_BEGIN




/**
	\ingroup Animation
	\class AnimationGroupSequential
	\brief Can hold and play animations in a sequential order, including other groups of animations
*/
class NEPHILIM_API AnimationGroupSequential : public AnimationGroup {
public:
	/// Default construction
	AnimationGroupSequential();

	/// Called when the animation is updating
	/// \return MUST return the remaining time not used by the animation
	/// This is essential as in a play list of animations, when one finished, the next updates immediately.
	virtual float onUpdate(float elapsedTime);

	/// Called to trigger the start of this animation
	void play();

private:
	unsigned int m_index;
};

NEPHILIM_NS_END
#endif // NephilimAxSequence_h__