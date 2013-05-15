#include <Nephilim/BrowserPreloader.h>

#include <Nephilim/ASEngine.h>
#include "AS/aswrappedcall.h"

NEPHILIM_NS_BEGIN

/// Registers the class for scripting
bool registerBrowserPreloader(ASEngine* engine)
{
	engine->exportReferenceDataType("BrowserPreloader");

	asIScriptEngine* as = engine->getASEngine();
	
	if(engine->getPortableMode())
	{
		// must register generic
		as->RegisterObjectMethod("BrowserPreloader", "void download(string, string)", WRAP_MFN(BrowserPreloader, download), asCALL_GENERIC);
	}
	else
	{
		// normal registration
		as->RegisterObjectMethod("BrowserPreloader", "void download(string, string)", asMETHOD(BrowserPreloader, download), asCALL_THISCALL);
	}

	return true;
}

/// Launch and wait for the end
void BrowserPreloader::run()
{

};

/// Blindly attempts to download the file -- DEBUG ONLY
void BrowserPreloader::download(String source, String destination)
{
	onRequestDownload(source, destination);
};

NEPHILIM_NS_END