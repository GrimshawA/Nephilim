#include <Nephilim/Plugins/Plugin.h>
#include <Nephilim/Foundation/Logging.h>

#ifdef NEPHILIM_WINDOWS
#include <windows.h>
#endif

NEPHILIM_NS_BEGIN

Plugin::Plugin()
{

}

Plugin::Plugin(const String& filename)
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


Plugin::~Plugin()
{
	if (mHandle)
	{
		#ifdef NEPHILIM_WINDOWS
		FreeLibrary(static_cast<HMODULE>(mHandle));
		#endif
	}
}

/// Shorthand to check if its a loaded instance
Plugin::operator bool()
{
	return isLoaded();
}

/// Check if this is a live instance of the plugin
bool Plugin::isLoaded()
{
	return mHandle != nullptr;
}

/// Get the address of the function
void* Plugin::getFunctionAddress(const String& func_name)
{
#ifdef NEPHILIM_WINDOWS
	return GetProcAddress((HMODULE)mHandle, func_name.c_str());
#endif

	return nullptr;
}

NEPHILIM_NS_END