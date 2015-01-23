#ifndef NephilimPlugin_h__
#define NephilimPlugin_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Foundation/String.h>

NEPHILIM_NS_BEGIN

/**
	\class PluginLoader
	\brief Loads a single plugin dynamically at runtime
*/
class NEPHILIM_API PluginLoader
{
public:

	void* mHandle = nullptr;

public:

	/// Construct the plugin without initializing
	PluginLoader();

	/// Construct the plugin from its file
	PluginLoader(const String& filename);

	/// Ensure destruction of the plugin instance
	~PluginLoader();

	/// Check if this is a live instance of the plugin
	bool isLoaded();

	/// Shorthand to check if its a loaded instance
	operator bool();

	/// Get the address of the function
	void* getFunctionAddress(const String& func_name);
};

NEPHILIM_NS_END
#endif // NephilimPlugin_h__
