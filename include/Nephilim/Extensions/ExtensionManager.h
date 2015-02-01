#ifndef NephilimExtensionManager_h__
#define NephilimExtensionManager_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Foundation/String.h>

#include <vector>

NEPHILIM_NS_BEGIN

/*
	\class ExtensionManager
	\brief Manages all extensions the engine is using and knows about
*/
class NEPHILIM_API ExtensionManager
{
public:

	struct TrackedExtension
	{
		String filename;
	};

	struct LoadedExtension
	{
		String filename;
	};

	/// List of every plugin we know about, loaded or not
	std::vector<TrackedExtension> trackedExtensions;

	/// List of every plugin currently loaded in the engine
	std::vector<LoadedExtension>  loadedExtensions;
};

NEPHILIM_NS_END
#endif // NephilimExtensionManager_h__
