#ifndef Range_h__
#define Range_h__

#include "Platform.h"

NEPHILIM_NS_BEGIN

/**
	\ingroup Foundation
	\class Range
	\brief An interval of values
*/
template<typename T>
class NEPHILIM_API Range{
public:
	T begin;
	T end;
};

NEPHILIM_NS_END
#endif // Range_h__
