#include "Nephilim/Platform.h"
#include "Nephilim/ScriptGame.h"
/*#include "Nephilim/Text.h"*/
#include "Nephilim/Window.h"
#include "Nephilim/Sprite.h"
#include "Nephilim/Sound.h"
#include "Nephilim/Kinesis.h"
#include "Nephilim/FileInterface.h"
#include "Nephilim/TextStream.h"

#include <iostream>
using namespace std;

NEPHILIM_NS_BEGIN

/// Initializes the scripted game from a specific script
ScriptGame::ScriptGame(const String& startupScript) : GameCore(){
	m_startupScript = startupScript;
}

/// Called when the game is instanced, calls int main() on the starter script
void ScriptGame::onCreate(){
	/*renderer = createRenderer(NULL);
	grenderer = renderer.get();

	asEngine.exportStrings();
	asEngine.exportFiles();
	asEngine.exportMath();
	asEngine.exportBasicEngine();
	asEngine.exportBasicGameCore();
	asEngine.exportEvents();
	asEngine.exportBasicGraphics();
	asEngine.exportKinesis();	
	asEngine.exportContentBanks();
	asEngine.exportSoundGameCore();
	asEngine.exportRocketUi();
	asEngine.exportAnimations();
	asEngine.exportParticleSystems();

	asEngine.exportGameAs("myGame", this);

	asEngine.exportGlobalProperty("SceneRenderer Renderer", renderer.get());

	//p->drawDebug(renderer.get());
	exportScripts();

	//RocketContext *c = RocketContext::create("core_ui", Vec2i(1024,768));
	RocketPlugin::instance().loadFont("pirulen.ttf");
	myMainScript = asEngine.loadScript("main.as");
	if(myMainScript){
		myCreateFunc = myMainScript->getFunctionIdByName("void onCreate()");
		myEventFunc = myMainScript->getFunctionIdByName("void onEvent(Event@)");
		myUpdateFunc = myMainScript->getFunctionIdByName("void onUpdate(float)");
		myRenderFunc = myMainScript->getFunctionIdByName("void onRender()");
		
		myMainScript->call(myCreateFunc);
	}
	else{
		this->close();
		std::cout<<"Finished execution with errors."<<std::endl;
		system("pause");
	}*/


	m_renderer = Renderer::createAutomaticRenderer(&getWindow());

	TESTLOG("Before texture load")
//	m_texture.loadFromFile("basic.png");
	TESTLOG("After texture load")
	//m_sprite.setTexture(m_texture);
	
	/// Scripting engine preparation
	m_engine.exportStrings();
	m_engine.exportEvents();
	m_engine.exportGraphics();
	m_engine.exportKinesis();

	m_engine.exportGlobalProperty("Renderer renderer", m_renderer);

	/// Prepare the main script
	m_script = m_engine.loadScript(m_startupScript);
	if(m_script){
		m_script->call(String("void onCreate()"));
	}
	
};

/// Draws the configured scene graph
/// If the direct render script is enabled, it is rendered after the other objects.
void ScriptGame::onRender(){
	//m_renderer->m_clearColor.r = 255;
	m_renderer->clear();
	View v;
	v.setRect(0,0,1024,768);

	/// Render the frame
	if(m_script){
		m_script->call(String("void onRender()"));
	}

	
	m_renderer->setView(v);
//	m_renderer->draw(m_sprite);
	//m_renderer->display();
	m_renderer->drawDebugCircle(Vec2f(200,200), 30, Vec2f(), Color::Red);

	getWindow().swapBuffers(); //tempo
	
};

/// Called when an event is fired.
void ScriptGame::onEvent(Event &event){
	if(m_script){
		m_script->prepareMethod(String("void onEvent(Event@)"));
		m_script->prepareMethodArgument(0, (void*)(&event), ScriptArgumentTypes::Object);
		m_script->call();
	}
};

/// Called when the game is updating
void ScriptGame::onUpdate(Time time){
	if(m_script){
		float elapsedTime = time.asSeconds();
		m_script->prepareMethod(String("void onUpdate(float)"));
		m_script->prepareMethodArgument(0, &elapsedTime, ScriptArgumentTypes::Float);
		m_script->call();
	}
};

/// Exports all necessary functions to scripts
void ScriptGame::exportScripts(){
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
	ScriptGame* game = new ScriptGame();
	game->entryPointScript = myEntryPoint;
	return game;
};

NEPHILIM_NS_END