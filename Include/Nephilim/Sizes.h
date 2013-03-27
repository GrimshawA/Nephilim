#ifndef PARABOLA_SIZES_H
#define PARABOLA_SIZES_H

#include "Platform.h"
#include "Strings.h"

PARABOLA_NAMESPACE_BEGIN

class PARABOLA_API Sizes{
public:
	static unsigned long getSize(const String &val){
		return sizeof(unsigned int) + val.size() * sizeof(char);
	}
};

PARABOLA_NAMESPACE_END
#endif