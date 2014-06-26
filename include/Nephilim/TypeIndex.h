#ifndef NephilimTypeIndex_h__
#define NephilimTypeIndex_h__

#include <Nephilim/Platform.h>
#include <typeinfo>

NEPHILIM_NS_BEGIN

	

class TypeIndex
{
public:
	const std::type_info* mNativeType;
};

NEPHILIM_NS_END
#endif // NephilimTypeIndex_h__
