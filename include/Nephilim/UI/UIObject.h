#ifndef NephilimUIObject_h__
#define NephilimUIObject_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Foundation/Object.h>

#include <sigc++/sigc++.h>
#include <vector>

NEPHILIM_NS_BEGIN

class UICore;

/**
	\class UIObject
	\brief The base class for UI objects

	UI is naturally a thing that relates closely to OOP programming.
	As such, this is the base class that provides common ground for 
	UI objects. This is pretty lightweight and many UI aspects
	have objects, this UI system uses composition rather than inheritance
	to make up its behavior.

	This would be the equivalent of GameObject for UI facilities,
	which live in a "parallel" world to the World module.

	An UIObject does not have any kind of visual representation,
	but it is hierarchic. This can be a full 3D "scene graph" with
	3D ui too.
*/
class NEPHILIM_API UIObject : public Object, public sigc::trackable
{
public:
	/// Every UIObject needs to reference a UICore to function properly
	/// It is the resource provider as well as other utilities
	/// This is not an owning reference, it must be destroyed somewhere.
	UICore*                _core = nullptr;

public:

	/// Destructor
	virtual ~UIObject();

	/// Just a getter for the core
	UICore* getCore();
};

NEPHILIM_NS_END
#endif // NephilimUIObject_h__
