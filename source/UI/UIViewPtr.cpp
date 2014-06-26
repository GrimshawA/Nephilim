#include <Nephilim/UIView.h>

NEPHILIM_NS_BEGIN

/// Default initialization to NULL reference
UIViewPtr::UIViewPtr()
: mRef(NULL)
{

}

/// Automatic destruction of the UIView reference
/// In case the UIView is still inserted in a hierarchy, it is the responsability of the hierarchy to destroy it
/// If the UIView is loose then it is guaranteed to be destroyed
UIViewPtr::~UIViewPtr()
{
	if(mRef && !mRef->getParent())
	{
		delete mRef;
	}
}

NEPHILIM_NS_END