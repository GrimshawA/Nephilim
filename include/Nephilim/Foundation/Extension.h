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
class NEPHILIM_API Extension : public ReferencedObject
{
public:

	/// The instance name of this extension (comes from the plugin)
	String _name;


	

public:

	/// Destructor
	virtual ~Extension();

	/// Called when we want to unload an extension and all its resources prematurely
	virtual void Release();
};

NEPHILIM_NS_END
#endif // NephilimFoundationExtension_h__