#ifndef PARABOLA_BROWSERPLUGININSTANCE_H
#define PARABOLA_BROWSERPLUGININSTANCE_H

#include "Platform.h"
#include "Engine.h"
#include "Signals.h"
#include <SFML/System/Thread.hpp>
#include <SFML/System/Mutex.hpp>
#include <SFML/System/Lock.hpp>

#include <map>

PARABOLA_NAMESPACE_BEGIN
typedef void* WindowHandle;

/**
	\ingroup Core
	\class BrowserPluginInstance
	\brief This class manages an instance of the engine living under a html object element in a browser
*/
class PARABOLA_API BrowserPluginInstance{
public:
	/// Prepares an uninitialized engine for a browser frame
	BrowserPluginInstance();
	/// Ensures proper destruction of the engine living in a browser frame being destroyed
	~BrowserPluginInstance();

	/// The execution thread of this engine
	void mainThreadFunction();

	/// Shuts down the execution of the engine thread
	void finish();

	/// Starts the engine from an window handle
	void start(WindowHandle handle, std::map<String,String>& params, const String& webPageURL, const String& workingDirectory);

	sigc::signal<bool, String, String> getRemoteFile;

private:
	/// The thread running the engine 
	sf::Thread* m_mainThread;
	sf::Mutex m_runMutex;

	/// The running engine for the browser window
	Engine* m_engine;
	WindowHandle m_windowHandle;

	/// Thread shutdown order - thread safe
	bool m_finished;

public:

	bool doDownload(String s, String d);

	/// The thread controlling the engine and game
	void runThread();



	/// Get the URL path of the webpage running the plugin
	String getURL();

	/// Set the URL of the webpage
	void setURL(const String& url);

	/*
	sf::Thread m_executionThread;
	Engine m_sdk;
	WindowHandle m_windowHandle;
	std::map<String,String> m_params;
	*/
	/// The URL of the path where the plugin's HTML page is running
	String m_browserPageURL;
	String m_preloadScriptURL;
	std::map<String,String> m_params;
	String m_workingDirectory;
};

PARABOLA_NAMESPACE_END
#endif