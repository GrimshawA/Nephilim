#ifndef NephilimRazerComponentHandle_h__
#define NephilimRazerComponentHandle_h__

#include <Nephilim/Platform.h>

#include <vector>
#include <map>

NEPHILIM_NS_BEGIN
namespace rzr {

/**
	\class CHandle
	\brief Safe and quick way to reference components in arbitrary component managers

	This handle can be used to quickly query a component manager if the handle remains valid
	as well as getting a real object reference to manipulate from it.
*/
class NEPHILIM_API CHandle
{
public:
	Uint32 handle;
};

/**
	\class CPtr
	\brief Smart pointer to manipulate components as regular pointers

	By using handles instead of raw pointers, we assure it doesn't become invalid
*/
template<typename T>
class NEPHILIM_API CPtr
{
public:
	CHandle handle;

	T* operator->();
};

template<typename T>
T* CPtr<T>::operator->()
{
	return nullptr;
}

};
NEPHILIM_NS_END
#endif // NephilimRazerComponentHandle_h__
