#ifndef NephilimFoundationObject_h__
#define NephilimFoundationObject_h__

#include <Nephilim/Platform.h>

NEPHILIM_NS_BEGIN

/**
	\class Object
	\brief Superclass of most engine object classes
*/
class NEPHILIM_API Object
{
public:

	virtual void test()
	{}

	/// Destructor
	virtual ~Object();
};


class NEPHILIM_API ReferencedObject : public Object
{
private:
	int mObjectReferences;

public:

	/// Ensure the object ref count is initialized to 1
	ReferencedObject();

	/// Add a reference to the object
	void addReference();

	/// Remove the reference to the object
	void releaseReference();
};

template<typename T>
class NEPHILIM_API RefObjectPtr
{
private:

	T* obj;

public:

	/// Initialize in invalid state (nullptr)
	RefObjectPtr()
		: obj(nullptr)
	{

	}

	/// Initialize from a ReferencedObject ptr (and increment its references automatically)
	RefObjectPtr(T* objptr)
		: obj(nullptr)
	{
		reset(objptr);
	}

	~RefObjectPtr()
	{
		release();
	}
	
	/// Get the raw pointer, this is not recommended
	T* get()
	{
		return obj;
	}

	void release()
	{
		if (obj)
			static_cast<ReferencedObject*>(obj)->releaseReference();

		obj = nullptr;
	}

	/// Set a new ReferencedObject ptr to this smart pointer, releasing the reference from the previous
	void reset(ReferencedObject* objptr)
	{
		release();

		obj = objptr;

		static_cast<ReferencedObject*>(obj)->addReference();
	}

	/// Operator overload for accessing T directly
	T* operator->()
	{
		return obj;
	}

	/// Operator overload for accessing T directly
	const T* operator->() const
	{
		return obj;
	}

	/// Operator overload for getting a T& reference instead
	T& operator*()
	{
		return *obj;
	}

	/// Operator overload for getting a T& reference instead
	const T& operator*() const
	{
		return *obj;
	}
	
	/// Convenience to be able to check if the smart ptr is valid
	operator bool()
	{
		return obj != nullptr;
	}
};

NEPHILIM_NS_END
#endif // NephilimFoundationObject_h__
