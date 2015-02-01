#ifndef NephilimFoundationExtension_h__
#define NephilimFoundationExtension_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Foundation/Object.h>
#include <Nephilim/Foundation/String.h>

#include <vector>

NEPHILIM_NS_BEGIN

/**
	\class Extension
	\brief Interface for implementing different features to the engine

	Plugins (and not) can implement the extension interface to add
	features to the engine like audio, scripting, physics, AI and so on.
*/
class NEPHILIM_API Extension : public Object
{
public:

	/// Destructor
	virtual ~Extension();
};

NEPHILIM_NS_END
#endif // NephilimFoundationExtension_h__