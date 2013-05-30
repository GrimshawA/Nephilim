#ifndef NephilimAxTarget_h__
#define NephilimAxTarget_h__

#include "Platform.h"

NEPHILIM_NS_BEGIN

/**
	\ingroup Animation
	\class AxTarget
	\brief Base class for animation targets
*/
class NEPHILIM_API AxTarget
{
public:

	template<class T>
	void axSetNumber(T number)
	{
		printf("AxTarget SetNumber(%f)\n", number);
	}

};

/**
	\ingroup Animation
	\class AxConnectedTarget
	\brief Provides the ability to get animation results through signals
*/
class NEPHILIM_API AxConnectedTarget
{

};

NEPHILIM_NS_END
#endif // NephilimAxTarget_h__
