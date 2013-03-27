#ifndef BrowserPreloader_h__
#define BrowserPreloader_h__

#include "Platform.h"
#include "Signals.h"
#include "Strings.h"


PARABOLA_NAMESPACE_BEGIN

/**
	\ingroup Core
	\class BrowserPreloader
*/
class PARABOLA_API BrowserPreloader
{
public:
	/// Launch and wait for the end
	void run();

	/// Blindly attempts to download the file -- DEBUG ONLY
	void download(String source, String destination);

	sigc::signal<bool, String, String> onRequestDownload;
};

class ASEngine;

/// Registers the class for scripting
bool registerBrowserPreloader(ASEngine* engine);

PARABOLA_NAMESPACE_END
#endif // BrowserPreloader_h__
