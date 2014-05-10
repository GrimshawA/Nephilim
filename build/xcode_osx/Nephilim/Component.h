#ifndef NephilimRazerComponent_h__
#define NephilimRazerComponent_h__

#include <Nephilim/Platform.h>

#include <vector>
#include <map>

NEPHILIM_NS_BEGIN
namespace rzr {

/**
	\class Component
	\brief Represents one characteristic added to entities
*/
class NEPHILIM_API Component
{
public:

};

class NEPHILIM_API ComponentList
{
public:
	
};

template<class T>
class ComponentArray : public ComponentList
{
public:

	/// Array of components of a single type (Contiguous in memory)
	std::vector<T> mComponents;

	/// Maps entity id to its component
	std::map<Int32, size_t> mBinding;
};


};
NEPHILIM_NS_END
#endif // NephilimRazerComponent_h__
