#ifndef Range_h__
#define Range_h__

#include "Platform.h"

PARABOLA_NAMESPACE_BEGIN

/**
	\ingroup Foundation
	\class Range
	\brief An interval of values
*/
template<typename T>
class PARABOLA_API Range{
public:
	T begin;
	T end;
};

PARABOLA_NAMESPACE_END
#endif // Range_h__
