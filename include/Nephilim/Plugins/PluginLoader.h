#ifndef NephilimPlugin_h__
#define NephilimPlugin_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Foundation/FeatureProvider.h>
#include <Nephilim/Foundation/String.h>

NEPHILIM_NS_BEGIN

/**
	\class PluginLoader
	\brief Loads a single plugin dynamically at runtime
*/
class NEPHILIM_API PluginLoader
{
public:

	/// The feature this plugin implements
	FeatureProvider* mInstanceProvider = nullptr;

	void* mHandle = nullptr;

public:

	/// Construct the plugin without initializing
	PluginLoader();

	/// Construct the plugin from its file
	PluginLoader(const String& filename);

	/// Ensure destruction of the plugin instance
	~PluginLoader();

	/// Get the feature provided by this plugin
	/// Returns nullptr if the plugin failed to load correctly
	FeatureProvider* instance();

	/// Check if this is a live instance of the plugin
	bool isLoaded();

	/// Shorthand to check if its a loaded instance
	operator bool();

	/// Get the address of the function
	void* getFunctionAddress(const String& func_name);
};

NEPHILIM_NS_END
#endif // NephilimPlugin_h__
