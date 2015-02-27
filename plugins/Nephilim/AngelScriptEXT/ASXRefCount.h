#ifndef NephilimASXRefCount_h__
#define NephilimASXRefCount_h__

#include <Nephilim/Platform.h>

NEPHILIM_NS_BEGIN

/**
	\class ASXRefCount
	\brief Base class for reference counted objects

	The purpose of this class is to give a predictable reference counting behavior
	to C++ registered types to AngelScript. (Applies only for reference types, and not value)
*/
class NEPHILIM_API ASXRefCount
{
public:

	template<class T>
	static T* instance()
	{
		T* object = new T();
		object->numReferences = 1;
		return object;
	}

	static void addRef(ASXRefCount* obj)
	{
		obj->numReferences ++;
	}

	static void releaseRef(ASXRefCount* obj)
	{
		obj->numReferences --;
		if(obj->numReferences == 0)
		{
			delete obj;
		}
	}

	int numReferences;
};

NEPHILIM_NS_END
#endif // NephilimASXRefCount_h__
