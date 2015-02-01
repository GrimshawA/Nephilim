#include <Nephilim/Foundation/PluginLoader.h>
#include <Nephilim/Foundation/Logging.h>

#ifdef NEPHILIM_WINDOWS
#include <windows.h>
#endif

NEPHILIM_NS_BEGIN

typedef Object*(*CreateInstanceFuncPtr)();

PluginLoader::PluginLoader()
{

}

PluginLoader::PluginLoader(const String& filename)
{
#ifdef NEPHILIM_WINDOWS
	HINSTANCE hGetProcIDDLL = LoadLibraryA(filename.c_str());

	if (!hGetProcIDDLL) {
		Log("NO DLL");
	}
	else
	{
		Log("Plugin: load successful (%s)", filename.c_str());
		mHandle = hGetProcIDDLL;
	}
#endif
}


PluginLoader::~PluginLoader()
{
	if (mHandle)
	{
		#ifdef NEPHILIM_WINDOWS
		FreeLibrary(static_cast<HMODULE>(mHandle));
		#endif
	}
}

/// Get the feature provided by this plugin
/// Returns nullptr if the plugin failed to load correctly
Object* PluginLoader::instance()
{
	if (mInstance)
	{
		return mInstance;
	}
	else
	{
		if (isLoaded())
		{
			CreateInstanceFuncPtr CreateInstanceFunc = (CreateInstanceFuncPtr)getFunctionAddress("CreateInstance");
			if (CreateInstanceFunc)
				mInstance = CreateInstanceFunc();
		}
		return mInstance;
	}
}

/// Shorthand to check if its a loaded instance
PluginLoader::operator bool()
{
	return isLoaded();
}

/// Check if this is a live instance of the plugin
bool PluginLoader::isLoaded()
{
	return mHandle != nullptr;
}

/// Get the address of the function
void* PluginLoader::getFunctionAddress(const String& func_name)
{
#ifdef NEPHILIM_WINDOWS
	return GetProcAddress((HMODULE)mHandle, func_name.c_str());
#endif

	return nullptr;
}

NEPHILIM_NS_END