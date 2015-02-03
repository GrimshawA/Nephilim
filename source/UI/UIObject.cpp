#include <Nephilim/UI/UIObject.h>

NEPHILIM_NS_BEGIN

/// Destructor
UIObject::~UIObject()
{

}

/// Just a getter for the core
UICore* UIObject::getCore()
{
	return _core;
}

NEPHILIM_NS_END
