#include <Nephilim/Platform.h>
#ifndef PARABOLA_ANDROID

#include <Nephilim/BrowserPluginInstance.h>
#include <Nephilim/ScriptedGameCore.h>

#include <SFML/System.hpp>

NEPHILIM_NS_BEGIN

/// Prepares the needed resources to run
BrowserPluginInstance::BrowserPluginInstance() : m_finished(false), m_engine(NULL){
	m_mainThread = new sf::Thread(&BrowserPluginInstance::mainThreadFunction, this);
};

/// Ensures proper destruction of the engine living in a browser frame being destroyed
BrowserPluginInstance::~BrowserPluginInstance(){
	delete m_mainThread;

	if(m_engine){ // thread finished abnormally, dealocate
		delete m_engine;
		m_engine = NULL;
	}
};

/// The execution thread of this engine
void BrowserPluginInstance::mainThreadFunction(){
	
	// init
	m_engine = new Engine();
//	m_engine->createFromHandle(m_windowHandle);

	// get preload script - mandatory
	m_preloadScriptURL = m_browserPageURL + m_params["startup"];
	m_preloadScriptURL.removeUntilReverse('/');
	m_preloadScriptURL += "/"; // contains the URL where the preload script lies

	String preloadFileName = m_params["startup"];
	if(preloadFileName.find_first_of('/') != preloadFileName.npos)
	{
		preloadFileName.erase(preloadFileName.begin(), preloadFileName.begin() + preloadFileName.find_last_of('/') + 1);
	}
	doDownload(preloadFileName , m_workingDirectory + "preload.as");
	
	ScriptedGameCore* game = new ScriptedGameCore(); 
	game->onRequestDownload.connect(MAKE_SLOT_LOCAL(BrowserPluginInstance, doDownload));
	game->enablePreloadStep(true);
	game->setPreloadScript("preload.as");
	game->setFileRoot(m_workingDirectory);
	m_engine->execute(game);

	game->m_info = m_preloadScriptURL + preloadFileName + "\n" + m_workingDirectory;

	bool m_executeFrame = true;
	while(m_executeFrame){
		
		// loop step
//		m_engine->getWindow().setActive(true);
		m_engine->update();

		//m_engine->getWindow().setActive(false);

		// stall a little to avoid overload
		sf::sleep(sf::milliseconds(10));

		// check if the thread will execute the next step
		{
			sf::Lock boolLock(m_runMutex);
			if(m_finished){
				m_executeFrame = false;
				m_finished = false;
			}
		}
	}

	// shutdown - normal thread finish - safe destruction
	delete m_engine;
	m_engine = NULL;
	
};

/// Shuts down the execution of the engine thread
void BrowserPluginInstance::finish(){
	sf::Lock boolLock(m_runMutex);
	m_finished = true;
};

bool BrowserPluginInstance::doDownload(String s, String d)
{
	// Must make the source absolute
	return getRemoteFile(m_preloadScriptURL + s, d);
};


/// Starts the engine from an window handle
void BrowserPluginInstance::start(WindowHandle handle, std::map<String,String>& params, const String& webPageURL, const String& workingDirectory){
	
	m_browserPageURL = webPageURL;
	m_params = params;
	m_workingDirectory = workingDirectory;
	//m_executionThread.launch();
	//while(!thread_initialized){} // must wait

	/// Order the engine to start running, because the window is ready
	m_windowHandle = handle;
	m_mainThread->launch();
};

/// The thread controlling the engine and game
void BrowserPluginInstance::runThread(){
	/*thread_running = true;
	thread_initialized = false;

	/// some initialization
	
	//sf::Lock lock(m_globalMutex);
	m_sdk.createFromHandle(m_windowHandle);
	if(m_params.find("startup") != m_params.end()){
		m_sdk.getGameManager().addGameForExecution(new ScriptGame(m_params["startup"]));

	}
	else{
		m_sdk.getGameManager().addGameForExecution(new ScriptGame());
	}
	
		
	
	

	//m_sdk.getGameManager().addGameForExecution(new ScriptGame());

	while(m_sdk.isRunning()){
		thread_initialized = true;
		m_sdk.getWindow().setActive(true);
		m_sdk.update();
		//sf::sleep(sf::milliseconds(20));
		
	}

	/// some destruction
	thread_running = false;*/
};

/// Get the URL path of the webpage running the plugin
String BrowserPluginInstance::getURL(){
	return m_browserPageURL;
};

/// Set the URL of the webpage
void BrowserPluginInstance::setURL(const String& url){
	m_browserPageURL = url;
};


NEPHILIM_NS_END

#endif