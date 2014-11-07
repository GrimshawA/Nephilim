#ifndef NephilimResource_h__
#define NephilimResource_h__

#include <Nephilim/Platform.h>

NEPHILIM_NS_BEGIN

/**
	\class Resource
	\brief Hold a resource reference

	Meant to be used as Resource<Type> myAsset
	to reference a resource in the content manager.

	For example, a component can store a texture reference
	in a reference counted way, by having a member variable
	Resource<Texture2D> texture;

	This will let the content manager know whether or not there are any components using
	the resource at that time for smart deallocations, instead of keeping a raw
	pointer which could become invalid at any time.
*/
template<typename T>
class NEPHILIM_API Resource
{
public:
	T* ptr = nullptr;
};

NEPHILIM_NS_END
#endif //NephilimResource_h__