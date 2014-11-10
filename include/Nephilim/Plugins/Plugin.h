#ifndef NephilimPlugin_h__
#define NephilimPlugin_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Strings.h>

NEPHILIM_NS_BEGIN

/**
	\class Plugin
	\brief Handles a plugin instance for as long as it is alive
*/
class NEPHILIM_API Plugin
{
public:

	void* mHandle = nullptr;

public:

	/// Construct the plugin without initializing
	Plugin();

	/// Construct the plugin from its file
	Plugin(const String& filename);

	/// Ensure destruction of the plugin instance
	~Plugin();

	/// Check if this is a live instance of the plugin
	bool isLoaded();
};

NEPHILIM_NS_END
#endif // NephilimPlugin_h__
