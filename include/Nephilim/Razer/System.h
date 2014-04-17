#ifndef NephilimRazerSystem_h__
#define NephilimRazerSystem_h__

#include <Nephilim/Platform.h>

#include <typeindex>

NEPHILIM_NS_BEGIN
namespace rzr
{

/**
	\class System
	\brief Game system manager
*/
class NEPHILIM_API System
{
public:
	virtual void onComponentAdded(std::type_index type_index, void* cdata){}

	virtual ~System();
};

};
NEPHILIM_NS_END
#endif // NephilimRazerSystem_h__
