#include <Nephilim/Plugins/Plugin.h>
#include <Nephilim/Logger.h>

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

/// Check if this is a live instance of the plugin
bool Plugin::isLoaded()
{
	return mHandle != nullptr;
}

NEPHILIM_NS_END