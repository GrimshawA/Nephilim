#include <Nephilim/Foundation/Object.h>

NEPHILIM_NS_BEGIN

/// Destructor
Object::~Object()
{

}

/// Ensure the object ref count is initialized to 1
ReferencedObject::ReferencedObject()
: mObjectReferences(1)
{
}

/// Add a reference to the object
void ReferencedObject::addReference()
{
	++mObjectReferences;
}

/// Remove the reference to the object
void ReferencedObject::releaseReference()
{
	if (--mObjectReferences == 0)
	{
		delete this; // won't actually be a delete this
	}
}

NEPHILIM_NS_END