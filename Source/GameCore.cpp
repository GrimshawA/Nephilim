#include <Nephilim/GameCore.h>
#include <Nephilim/Engine.h>

#include <iostream>
using namespace std;

NEPHILIM_NS_BEGIN

/// Construct the game, its mandatory to call this base constructor when implementing GameCore
GameCore::GameCore() : m_stackedTime(0.f), m_updateStep(1.f / 60.f), m_windowTitle("No name window"), mCloseRequested(false){
#ifdef PARABOLA_ANDROID
	m_updateStep = 1.f / 30.f;
#endif


};

/// Get the window/screen handler
	Window& GameCore::getWindow()
	{
	    return *m_creator->m_surface.window;
	}

/// Sets the base directory to load resources from
void GameCore::setFileRoot(const String & path)
{
	m_fileSystemRoot = path;
};

/// Get the root for file loading on this game
String GameCore::getFileSystemRoot()
{
	return m_fileSystemRoot;
};

Renderer* GameCore::getRenderer()
{
	return m_creator->getRenderer();
}

/// Shutdown this game immediately
void GameCore::close(){
	mCloseRequested = true;
};

/// Set the name of the game
void GameCore::setName(const String& name)
{
	m_gameName = name;
};

/// Get the name of the game
String GameCore::getName()
{
	return m_gameName;
};

/// Set the fixed update step, or, the amount of time, in seconds, that will take between each update.
void GameCore::setUpdateStep(float step){
	m_updateStep = step;
};

/// Callback for updating the game
void GameCore::onUpdate(Time time){

};

/// Callback for rendering a frame
void GameCore::onRender(){

};

/// Callback when starting to execute the game
void GameCore::onCreate(){

};

/// Callback when an event happens
void GameCore::onEvent(Event &event){

};

/// Get the game window title
String GameCore::getWindowTitle(){
	return m_windowTitle;
};

/// Set the title of the window while the game is active
void GameCore::setWindowTitle(const String &title){
	m_windowTitle = title;
};

/// Inner update of the game
/// Will handle fixed update steps
/// Callbacks to onUpdate(Time time) when appropriate
void GameCore::innerUpdate(Time time){
	m_stackedTime += time.asSeconds();
	while(m_stackedTime >= m_updateStep){
		onUpdate(Time::fromSeconds(m_updateStep));
		m_stackedTime -= m_updateStep;
	}
};

/// Inner render of the game
/// Callbacks to onRender()
void GameCore::innerRender(){
	onRender();
};


	/*
/// Creates a fresh game
/// Defaults at 60Hz update rate.
GameCore::GameCore() : fixedUpdateStep(1.f / 60.f), myParent(NULL), accumulatedTime(0.f), myWindowTitle("Default Game Name"), activeDrawing(false){
	clearColor = Color::Transparent;
	myScriptEngine.myParent = this;
};

/// Get the assigned window
/// Returns a NULL smart pointer if no window exists
Window* GameCore::getWindow(){
	return myWindow;
};

/// Sets the primary window
/// It is mandatory that a window is set for onRender to be called.
void GameCore::setWindow(Window* window){
	myWindow = window;
};

/// Get the name of this game
String& GameCore::name(){
	return myName;
};

/// Runs a script command
void GameCore::runScript(const String &command){
	myScriptEngine.run(command);
};

/// Get a reference to the script engine
ScriptEngine& GameCore::scriptEngine(){
	return myScriptEngine;
};

/// Inner update is responsible to call the regular onUpdate
/// Also handles fixed time step
void GameCore::innerUpdate(Uint32 elapsedTime){
	accumulatedTime += (float)elapsedTime / 1000.f;
	while(accumulatedTime >= fixedUpdateStep){
		onUpdate(fixedUpdateStep);
		accumulatedTime -= fixedUpdateStep;
	}
};

/// Inner render will check if there is an associated window, and only in that case it will draw into it
/// Calls SetActive() on the window, clears the buffer and displays it.
void GameCore::innerRender(){
	if(myWindow && activeDrawing){
		myWindow->setActive(true);
		myWindow->clear(clearColor);
		onRender();
		myWindow->display();
	}
};

/// Inner Create is responsible to proper initialize the game if the constructor is not called
void GameCore::innerCreate(){
	fixedUpdateStep = (1.f / 60.f);
	accumulatedTime = (0.f);
	activeDrawing = (false);
	myScriptEngine.myParent = this;
	clearColor = Color::Transparent;
	onCreate();
};


/// Inner Activate will do the intern preparations for the game to be drawing
void GameCore::innerActivate(){
	activeDrawing = true;
	if(myWindow){
		myWindow->setTitle(myWindowTitle);
	}
	onRenderFocus();
};

/// Inner Deactivate will do the preparations for the game to stop drawing
void GameCore::innerDeactivate(){
	activeDrawing = false;
	onRenderLostFocus();
};

/// Callback to draw on the window
void GameCore::onRender(){

};

/// Callback to handle the event
void GameCore::onEvent(const Event &event){

};

/// Callback to update the game state by elapsedTime seconds
void GameCore::onUpdate(float elapsedTime){

};

/// Callback when the game becomes the active drawing game
void GameCore::onRenderFocus(){

};

/// Callback when the game can't render anymore
void GameCore::onRenderLostFocus(){

};

/// Callback when the game was just instanced
void GameCore::onCreate(){

};

/// Callback when the game is about to be destroyed
void GameCore::onDestroy(){

};

/// Callback when the game enters the execution list
void GameCore::onUpdateFocus(){

};

/// Callback when the game is removed from the execution list
void GameCore::onUpdateLostFocus(){

};

/// Inner Event Check takes the associated window and gets events from it
void GameCore::innerEventCheck(){
	if(myWindow && activeDrawing){
		static Event event;
		while(myWindow->eventDispatcher().catchEvent(event, true)){
			onEvent(event);
		}
	}
};

/// Destroys this game at the end of the update
void GameCore::close(){
	if(myParent){
		myParent->destroy(this);
	}
};

/// Creates a renderer pointing at the render target passed in
/// If the target is NULL, it tries to bind the renderer to the current window
SceneRenderer* GameCore::createRenderer(RenderTarget *target){
	SceneRenderer* renderer = new SceneRenderer();

	// assign window
	if(target){
		renderer->setRenderTarget(*target);
	}
	else if(getWindow()){
		renderer->setRenderTarget(*getWindow());
	}

	return renderer;
};

/// Get the current window title
/// By default, it says "Default Game Name"
String& GameCore::windowTitle(){
	return myWindowTitle;
};

/// Set the window title
void GameCore::setWindowTitle(const String &title){
	myWindowTitle = title;
	if(activeDrawing && myWindow) myWindow->setTitle(title);
};


/// Get a sound player
SoundPlayer& GameCore::getSoundPlayer(const String &name){
	if(mySoundPlayers.find(name) == mySoundPlayers.end()){
		mySoundPlayers[name] = new SoundPlayer(this, name);
	}
	return *mySoundPlayers[name];
};

/// Destroys a sound player
void GameCore::removeSoundPlayer(const String &name){
	std::map<String, SoundPlayer*>::iterator it = mySoundPlayers.find(name);
	if(it != mySoundPlayers.end()){
		delete it->second;
		mySoundPlayers.erase(it);
	}
};

/// Get a content bank
/// If the selected content bank doesn't exist, it is created.
ContentBank& GameCore::getContentBank(const String &name){
	if(myContentBanks.find(name) == myContentBanks.end()){
		myContentBanks[name] = new ContentBank(this, name);
	}
	return *myContentBanks[name];
};

/// Destroy a content bank
void GameCore::removeContentBank(const String &name){
	std::map<String, ContentBank*>::iterator it = myContentBanks.find(name);
	if(it != myContentBanks.end()){
		delete it->second;
		myContentBanks.erase(it);
	}
};*/

NEPHILIM_NS_END
