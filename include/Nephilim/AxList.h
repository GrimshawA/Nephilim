#ifndef NephilimAxList_h__
#define NephilimAxList_h__

#include "Platform.h"
#include "AnimationInterface.h"

#include "AxBase.h"

#include <list>

NEPHILIM_NS_BEGIN

/**
	\ingroup Animation
	\class AxList
	\brief Processes multiple animations at the same time

	All animations are destroyed after finishing playing.
*/
class NEPHILIM_API AxList
{
public:

	/// Delete all animations
	~AxList();

	/// Commit a new animation for processing
	void commit(AxBase* animation);

	/// Updates the list of animations
	void update(float delta);

	std::list<AxBase*> m_animations; ///< Processing animation list
};




/**
	\ingroup Animation
	\class AnimationStall
	\brief Animation meant to stall only, if you need to skip some time until the next animation.
*/
class NEPHILIM_API AnimationStall : public AnimationInterface{
public:
	AnimationStall();

	AnimationStall(float duration);

	/// Called when the animation is updating
	/// \return MUST return the remaining time not used by the animation
	/// This is essential as in a play list of animations, when one finished, the next updates immediately.
	virtual float onUpdate(float elapsedTime);

	/// The standard update method for animations
	//void update(float elapsedTime);

	float m_duration;
	float elapsedSinceStart;
};

NEPHILIM_NS_END
#endif // NephilimAxList_h__