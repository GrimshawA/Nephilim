#ifndef PARABOLA_ANIMATIONGROUPPARALLEL_H
#define PARABOLA_ANIMATIONGROUPPARALLEL_H

#include "Platform.h"
#include "AnimationGroup.h"

NEPHILIM_NS_BEGIN

/**
	\ingroup Animation
	\class AnimationGroupParallel
	\brief Can hold and play multiple animations simultaneously, including other groups.
*/
class NEPHILIM_API AnimationGroupParallel: public AnimationGroup{
public:
	/// Update the group all at once
	void update(float elapsedTime);

private:

};

NEPHILIM_NS_END
#endif