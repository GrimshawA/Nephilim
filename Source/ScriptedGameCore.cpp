#include "Nephilim/Platform.h"
#include "Nephilim/CGL.h"
#include "Nephilim/ScriptedGameCore.h"

#include "Nephilim/Text.h"
#include "Nephilim/Window.h"
#include "Nephilim/Sprite.h"
#include "Nephilim/Sound.h"
#include "Nephilim/Kinesis.h"
#include "Nephilim/FileInterface.h"
#include "Nephilim/TextStream.h"
#include "Nephilim/NStateImage.h"
#include "Nephilim/NStateCustom.h"

#include <Nephilim/CGL.h>


#include <Nephilim/ASEngine.h>
#include "AS/aswrappedcall.h"

#ifdef PARABOLA_DESKTOP
#include <SFML/Audio/Music.hpp>
#endif

#include <iostream>
using namespace std;

PARABOLA_NAMESPACE_BEGIN

void MusicPlayer::play(const String& name)
{
#ifdef PARABOLA_DESKTOP
	sf::Music* music = new sf::Music();
	music->openFromFile(name);
	music->play();
#elif defined PARABOLA_ANDROID
	AndroidInterface::playMusic(name);
#endif
}

void vibrate(int ms)
{

#if defined PARABOLA_ANDROID
		AndroidInterface::vibrate(ms);
#endif
}



void registerScriptedGameCore(ASEngine* engine)
{
	engine->exportReferenceDataType("ScriptedGameCore");
	engine->exportReferenceDataType("ScriptEngine");
	engine->exportReferenceDataType("UIManager");
	engine->exportReferenceDataType("UIWindow");
	engine->exportReferenceDataType("UISurface");
	engine->exportReferenceDataType("UIControl");
	engine->exportReferenceDataType("Music");
	engine->exportReferenceDataType("Slot");

	if(engine->getPortableMode())
	{
		engine->getASEngine()->RegisterObjectMethod("UIManager", "UIWindow@ create(const string &in)", WRAP_MFN(UIManager, create), asCALL_GENERIC);
		engine->getASEngine()->RegisterObjectMethod("UIManager", "void draw(const string &in, Renderer@)", WRAP_MFN(UIManager, draw), asCALL_GENERIC);

		engine->getASEngine()->RegisterObjectMethod("UIWindow", "void messageBox(const string &in)", WRAP_MFN(UIWindow, showMessageBox), asCALL_GENERIC);
		engine->getASEngine()->RegisterObjectMethod("UIWindow", "UISurface@ addSurface(const string &in)", WRAP_MFN(UIWindow, addSurface), asCALL_GENERIC);
		engine->getASEngine()->RegisterObjectMethod("UIWindow", "void setLanguage(const string &in)", WRAP_MFN(UIWindow, setLanguage), asCALL_GENERIC);

		engine->getASEngine()->RegisterObjectMethod("UISurface", "void addControl(UIControl@)", WRAP_MFN(UISurface, addControl), asCALL_GENERIC);
		engine->getASEngine()->RegisterObjectMethod("UISurface", "void bindSignal(const string& in, Slot@)", WRAP_MFN(UISurface, bindSignal), asCALL_GENERIC);

		engine->getASEngine()->RegisterObjectMethod("Music", "void play(const string& in)", WRAP_MFN(MusicPlayer, play), asCALL_GENERIC);

		engine->getASEngine()->RegisterObjectMethod("ScriptedGameCore", "void toggleConsole()", WRAP_MFN(ScriptedGameCore, toggleConsole), asCALL_GENERIC);

		engine->getASEngine()->RegisterGlobalFunction("void vibrate(int)", WRAP_FN(vibrate), asCALL_GENERIC);

	}
	else
	{
		engine->getASEngine()->RegisterObjectMethod("UIManager", "UIWindow@ create(const string &in)", asMETHOD(UIManager, create), asCALL_THISCALL);
		engine->getASEngine()->RegisterObjectMethod("UIManager", "void draw(const string &in, Renderer@)", asMETHOD(UIManager, draw), asCALL_THISCALL);


		engine->getASEngine()->RegisterObjectMethod("UIWindow", "void messageBox(const string &in)", asMETHOD(UIWindow, showMessageBox), asCALL_THISCALL);
		engine->getASEngine()->RegisterObjectMethod("UIWindow", "UISurface@ addSurface(const string &in)", asMETHOD(UIWindow, addSurface), asCALL_THISCALL);
		engine->getASEngine()->RegisterObjectMethod("UIWindow", "void setLanguage(const string &in)", asMETHOD(UIWindow, setLanguage), asCALL_THISCALL);

		engine->getASEngine()->RegisterObjectMethod("UISurface", "void addControl(UIControl@)", asMETHOD(UISurface, addControl), asCALL_THISCALL);
		engine->getASEngine()->RegisterObjectMethod("UISurface", "void bindSignal(const string& in, Slot@)", asMETHOD(UISurface, bindSignal), asCALL_THISCALL);


		engine->getASEngine()->RegisterObjectMethod("Music", "void play(const string& in)", asMETHOD(MusicPlayer, play), asCALL_THISCALL);

		engine->getASEngine()->RegisterObjectMethod("ScriptedGameCore", "void toggleConsole()", asMETHOD(ScriptedGameCore, toggleConsole), asCALL_THISCALL);

		engine->getASEngine()->RegisterGlobalFunction("void vibrate(int)", asFUNCTION(vibrate), asCALL_CDECL);
	}

	engine->getASEngine()->RegisterObjectProperty("ScriptedGameCore", "StateStack states", asOFFSET(ScriptedGameCore, m_states));
	engine->getASEngine()->RegisterObjectProperty("ScriptedGameCore", "ScriptEngine scripts", asOFFSET(ScriptedGameCore, m_scripting));
	engine->getASEngine()->RegisterObjectProperty("ScriptedGameCore", "ContentBank content", asOFFSET(ScriptedGameCore, m_content));
	engine->getASEngine()->RegisterObjectProperty("ScriptedGameCore", "Window@ window", asOFFSET(ScriptedGameCore, m_window));
	//engine->getASEngine()->RegisterObjectProperty("ScriptedGameCore", "UIManager ui", asOFFSET(ScriptedGameCore, m_ui));
	engine->getASEngine()->RegisterObjectProperty("ScriptedGameCore", "Music music", asOFFSET(ScriptedGameCore, m_music));
};

ScriptedGameCore::ScriptedGameCore()
	:	GameCore(),
		m_requiresPreload(false)
{
	m_states.m_parent = this;
};

/// Sets the preload script. This is only useful before the onCreate() method
void ScriptedGameCore::setPreloadScript(const String& script)
{
	m_preloadScriptPath = script;
};

/// Enable or disable the preload step, important in browsers to cache resources
void ScriptedGameCore::enablePreloadStep(bool enable)
{
	m_requiresPreload = enable;

};


/// Only called when the preload is finished so the game can start

#ifdef PARABOLA_ANDROID
#define GL_GLEXT_PROTOTYPES
#include <GLES/gl.h>
#include <GLES/glext.h>
#include <GLES/glplatform.h>
#else

#endif


/// Called when the game is instanced, calls int main() on the starter script
void ScriptedGameCore::onCreate(){
	setUpdateStep(1.f / 100.f);

	m_window = &getWindow();

	// Export base functionality
	m_scripting.exportStrings();
	m_scripting.exportBasicEngine();
	//m_scripting.exportBasicGameCore();
	m_scripting.exportGraphics();
	m_scripting.exportEvents();
	//m_scripting.exportFiles();
	registerScopedFile(&m_scripting);
	m_scripting.exportMath();
	registerContentBank(&m_scripting);
	registerStateStack(&m_scripting);
	registerScriptedGameCore(&m_scripting);
	registerBrowserPreloader(&m_scripting);
	registerNStateImage(&m_scripting);
	registerNStateCustom(&m_scripting);
	registerSprite(&m_scripting);
	registerView(&m_scripting);
	registerUIButton(&m_scripting);

	m_scripting.exportGlobalProperty("ScriptedGameCore game", this);

	m_content.m_rootPath = m_fileSystemRoot;

	m_ui.area = FloatRect(0,0,getWindow().getWidth(), getWindow().getHeight());

	// PreLoad the game
	ASScript* preloadScript = m_scripting.loadScript(m_fileSystemRoot + m_preloadScriptPath);
	if(preloadScript)
	{
		cout<<"=> Loaded preload script"<<endl;

		m_preloader.onRequestDownload.connect(MAKE_SLOT_LOCAL(ScriptedGameCore, doDownload));

		/// Get main script path - if the function is missing the result is empty

		m_mainScriptPath = preloadScript->fastCall<String>("string getMainScript()");
		setName(preloadScript->fastCall<String>("string getName()"));

		if(m_requiresPreload)
		{
			// Im on the browser, need to cache resources first
			preloadScript->prepareMethod("void preload(BrowserPreloader@)");
			preloadScript->prepareMethodArgument(0, &m_preloader, ScriptArgumentTypes::Object);
			preloadScript->call();

			// now launch the loading task in parallel and wait to launch the game
			m_preloader.run();

			// HACK: for now, preloading is not enabled
			m_requiresPreload = false;
		}
	}
	else
	{
		// Error - no preload script
		cout<<"=> CRITICAL: Failed to load preload script"<<endl;
	}

	/// In case we don't need preload of resources - start immediately, otherwise it will be done later
	if(!m_requiresPreload)
	{
		startupGame();
	}



	getWindow().setFramerateLimit(30);
	m_renderer = Renderer::createAutomaticRenderer(&getWindow());








	/*TESTLOG("CREATING buffer")
	GLuint fbo;
	glGenFramebuffersOES(1, &fbo);
	if(!fbo)
	{
		TESTLOG("FAILED")
	}
	TESTLOG("CREATED")*/

	const unsigned char* str = glGetString(GL_EXTENSIONS);
	PRINTLOG("DD", "EXTENSIONS: %s\n", str);

};

/// Toggles the built-in console
void ScriptedGameCore::toggleConsole()
{
	cout<<"Enabling Console"<<endl;
};

void ScriptedGameCore::startupGame()
{
	// Create the game
	m_mainScript = m_scripting.loadScript(m_fileSystemRoot + m_mainScriptPath);
	if(m_mainScript)
	{
		cout<<"=> Loaded main script"<<endl;

		m_mainScript->call(String("void onCreate()"));

		m_states.processWaitList();
	}
	else
	{
		cout<<"=> CRITICAL: Failed to load main script"<<endl;
	}

};
/// Draws the configured scene graph
/// If the direct render script is enabled, it is rendered after the other objects.
void ScriptedGameCore::onRender(){
	//m_renderer->m_clearColor.r = 255;
	m_renderer->clear();
	View v;
	v.setRect(0,0,1024,768);

	/// Render the frame
	/*if(m_script){
		m_script->call(String("void onRender()"));
	}*/

	m_renderer->setView(v);
//	m_renderer->draw(m_sprite);
	//m_renderer->display();
	//m_renderer->drawDebugCircle(Vec2f(circleX,200), 30, Vec2f(), Color::Red);


	m_states.drawStates(m_renderer);

	// dirty rendering
	if(m_mainScript)
	{
		m_mainScript->prepareMethod(String("void onRender(Renderer@)"));
		m_mainScript->prepareMethodArgument(0, m_renderer, ScriptArgumentTypes::Object);
		m_mainScript->call();
	}



	Text t;
	t.setString(String("[") + getName() + String("]") + String("Preload Script: ")  + m_preloadScriptPath);

	Text t2;
	t2.setCharacterSize(15);
	t2.setPosition(0, 50);
	String finalS = "Log: " + m_info;
	t2.setString(finalS);
//
// 	Font brut;
// 	brut.loadFromFile("Brutality.ttf");
// 	Text txt;
// 	txt.setFont(brut);
// 	txt.setString("Hello Brutality test!");
// 	txt.setCharacterSize(40);
// 	txt.setPosition(100,500);
// 	txt.setColor(Color::Red);
// 	m_renderer->draw(txt);

	//m_renderer->draw(t);
	//m_renderer->draw(t2);

	getWindow().swapBuffers(); //tempo
};

bool ScriptedGameCore::doDownload(String s, String d)
{
	// Save the file locally to the base file system root
	return onRequestDownload(s, m_fileSystemRoot + d);
};

/// Called when an event is fired.
void ScriptedGameCore::onEvent(Event &event){

	if(event.type == Event::Resized)
	{
		PRINTLOG("Resize", "Resize: %d    %d\n", event.size.width, event.size.height);

		for(std::map<String,UIWindow*>::iterator it = m_ui.m_windows.begin(); it != m_ui.m_windows.end(); it++)
		{
			(*it).second->setRect(FloatRect(0,0,event.size.width, event.size.height));
		}
	}

	if(event.type == Event::Resume)
	{
		TESTLOG("RESUME CONTEXT LOST!!!\n");
	}


	m_states.propagateEvent(event);



	// dirty rendering
	if(m_mainScript)
	{
		m_mainScript->prepareMethod(String("void onEvent(Event@)"));
		m_mainScript->prepareMethodArgument(0, &event, ScriptArgumentTypes::Object);
		m_mainScript->call();
	}

	for(std::map<String,UIWindow*>::iterator it = m_ui.m_windows.begin(); it != m_ui.m_windows.end(); it++)
	{
		(*it).second->pushEvent(event);
	}


	if(event.type == Event::MouseWheelMoved  || event.type == Event::TouchPressed){
		circleX += 20;
	}

	if(event.type == Event::KeyPressed && event.key.code == Keyboard::AndroidBack)
	{
#ifdef PARABOLA_ANDROID
		AndroidInterface::closeActivity();
		TESTLOG("BACK!!!!!");
#endif
	}
};

/// Called when the game is updating
void ScriptedGameCore::onUpdate(Time time){
	m_states.updateStates(time);

	// dirty rendering
	if(m_mainScript)
	{
		float elapsedTime = time.asSeconds();
		m_mainScript->prepareMethod(String("void onUpdate(float)"));
		m_mainScript->prepareMethodArgument(0, &elapsedTime, ScriptArgumentTypes::Float);
		m_mainScript->call();
	}
};

/// Exports all necessary functions to scripts
void ScriptedGameCore::exportScripts(){
	//asIScriptEngine *engine = asEngine.getASEngine();





	//engine->RegisterGlobalFunction("void enableRenderScript(const string &in, const string &in)", asFUNCTION(enableRenderScript), asCALL_CDECL);
	//engine->RegisterGlobalFunction("void drawText(const string &in, int, int)", asFUNCTION(drawdebug), asCALL_CDECL);
	//engine->RegisterGlobalFunction("void playSound(const string &in)", asFUNCTION(playsounddebug), asCALL_CDECL);
	//engine->RegisterGlobalFunction("bool isKeyPressed(int)", asFUNCTION(iskeydebug), asCALL_CDECL);
	//engine->RegisterGlobalFunction("void drawImage(const string &in, int , int)", asFUNCTION(drawimagedebug), asCALL_CDECL);



	//engine->RegisterObjectProperty(")

};

/************************************************************************/
/* Instancer                                                            */
/************************************************************************/
/// Prepares this instancer to create ScriptGame named as desired, and with entry point wherever wanted
ScriptGameInstancer::ScriptGameInstancer(String name, String entryPoint){
	myName = name;
	myEntryPoint = entryPoint;
};

/// Instances the ScriptGame
GameCore* ScriptGameInstancer::Instance(){
	ScriptedGameCore* game = new ScriptedGameCore();
	game->entryPointScript = myEntryPoint;
	return game;
};

PARABOLA_NAMESPACE_END
