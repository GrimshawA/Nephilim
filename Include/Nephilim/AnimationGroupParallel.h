#ifndef PARABOLA_ANIMATIONGROUPPARALLEL_H
#define PARABOLA_ANIMATIONGROUPPARALLEL_H

#include "Platform.h"
#include "AnimationGroup.h"

PARABOLA_NAMESPACE_BEGIN

/**
	\ingroup Animation
	\class AnimationGroupParallel
	\brief Can hold and play multiple animations simultaneously, including other groups.
*/
class PARABOLA_API AnimationGroupParallel: public AnimationGroup{
public:
	/// Update the group all at once
	void update(float elapsedTime);

private:

};

PARABOLA_NAMESPACE_END
#endif