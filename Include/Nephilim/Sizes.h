#ifndef PARABOLA_SIZES_H
#define PARABOLA_SIZES_H

#include "Platform.h"
#include "Strings.h"

NEPHILIM_NS_BEGIN

class NEPHILIM_API Sizes{
public:
	static unsigned long getSize(const String &val){
		return sizeof(unsigned int) + val.size() * sizeof(char);
	}
};

NEPHILIM_NS_END
#endif