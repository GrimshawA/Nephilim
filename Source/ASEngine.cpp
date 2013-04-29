#include "Nephilim/ASEngine.h"
#include "Nephilim/File.h"
#include "Nephilim/GameCore.h"
#include "Nephilim/Engine.h"
#include "Nephilim/SoundPlayer.h"
#include "Nephilim/Vectors.h"
#include "Nephilim/Logger.h"


#undef GetObject

#include "AS/scriptbuilder.h"
#include "AS/scriptstdstring.h"
#include "AS/scriptarray.h"
#include "AS/scriptany.h"
#include "AS/scriptfile.h"
#include "AS/scriptmath.h"
#include "AS/aswrappedcall.h"

using namespace std;
#include <iostream>
#include <algorithm>
#include <string.h>

NEPHILIM_NS_BEGIN

void dummy(void*){

}

void scriptstdprint(std::string in){
	TESTLOG(in.c_str())
}

static void ASMessageCallback(const asSMessageInfo *msg, void *param){
		if(!msg)return;
		const char *type = "ERR ";
		if( msg->type == asMSGTYPE_WARNING )
			type = "WARN";
		else if( msg->type == asMSGTYPE_INFORMATION )
			type = "INFO";

		//printf("%s (%d, %d) : %s : %s\n", msg->section, msg->row, msg->col, type, msg->message);
		PRINTLOG("AngelScript", "%s (%d, %d) : %s : %s\n", msg->section, msg->row, msg->col, type, msg->message)

};

ASEngine::ASEngine(){
	asEngine = asCreateScriptEngine(ANGELSCRIPT_VERSION);
	if(!asEngine)
	{
		printf("COULD NOT CREATE AS ENGINE");
	}

	asEngine->SetMessageCallback(asFUNCTION(ASMessageCallback), 0, asCALL_CDECL);
	asEngine->SetEngineProperty(asEP_INIT_GLOBAL_VARS_AFTER_BUILD, false);


	if(!getPortableMode())
	{
#ifdef PARABOLA_ANDROID
		TESTLOG("ARM MODE!!!")
#endif
	}

	gameCoreBasic = false;
	gameCoreAdvanced = false;
	gameCoreSound = false;
	gameCoreExported = false;
	scriptBasic = false;
	engineBasic = false;
	exportedRenderer = false;
	exportedKinesis = false;
	exportedContentBanks = false;
	exportedRocket = false;
	exportedRocketInternal = false;
	exportedParticles = false;
};

/// Ensures proper destruction of the engine
ASEngine::~ASEngine(){
	asEngine->Release();
};

/// Returns the pointer to the internal angel script engine
/// Possible use could be to export functions.
asIScriptEngine* ASEngine::getASEngine(){
	return asEngine;
};

/// Returns true if compiling in the max compatibility profile, for mobile devices etc
bool ASEngine::getPortableMode(){
	return (strstr(asGetLibraryOptions(), "AS_MAX_PORTABILITY"));
};


/// Destroys a script from the engine
void ASEngine::unloadScript(const String &name){

};

/// Loads a script from a null terminated char buffer
ASScript* ASEngine::loadScriptFromMemory(const char* buffer, const String &scriptName){
	ASScript* asScript = NULL;

	CScriptBuilder Builder;
	int r;
	r = Builder.StartNewModule(asEngine, scriptName.c_str());
	if(r<0){
		//pLogger::Log(LogLevel::Critical, "Could not create a new Script Module.", "[ScriptEngine]");
		return NULL;
	}

	r = Builder.AddSectionFromMemory(buffer, scriptName.c_str());
	if(r<0){
				//pLogger::Log(LogLevel::Critical, "Could not stream file data into the Script Module.", "[ScriptEngine]");
				return NULL;
	}

	r = Builder.BuildModule();
	if(r<0){
				//pLogger::Log(LogLevel::Critical, "Could not compile the script file.", "[ScriptEngine]");
				return NULL;
	}

	asScript = new ASScript();
	asScript->myParent = this;
	asScript->myModule = asEngine->GetModule(scriptName.c_str());
	if(!asEngine->GetModule(scriptName.c_str())){
		cout<<"Failed to acquire module"<<endl;
	}
	else cout<<"Module: "<<asScript->myModule<<endl;

	return asScript;
};

/// Loads a script into the engine
/// Any functionality the script requires must be exported before loading it
/// \param name The name of the script to load, relative to the executable directory, or the added directories
/// \param alias An override for the name, as the search keyword of this script. Ignored if empty.
/// \param isByteCode When true, the script is assumed to be already compiled, and is loaded as bytecode.
/// \return ASScript structure to interact with the loaded script, NULL if failed to load.
/// \note The name specified or the alias may be already in use. In that case, a new name is generated and can be queried later.
/////////////////////////////////////////////////////////////////////////////////////////////////
ASScript* ASEngine::loadScript(const String &name, const String &alias, bool isByteCode){
	ASScript* asScript = NULL;

	CScriptBuilder Builder;
	int r;
	r = Builder.StartNewModule(asEngine, name.c_str());
	if(r<0){
		TESTLOG("Could not create a new Script Module.")
		return NULL;
	}

	if(isByteCode){

	}
	else{
#ifdef PARABOLA_ANDROID

		File* fp = new File();
		FileInterface::getAssetFile(fp, String(name), true);
		if(fp && fp->canRead()){
			fp->seek(0, SEEK_END);
			Int64 size = fp->tell();
			fp->seek(0);
			char *buffer = new char[size+1];
			String ss = "Angelscript loading script with " + String::number((unsigned long)size) + " bytes";
			//TESTLOG(ss.c_str())
			fp->read(buffer, size);
			buffer[(unsigned int)size] = '\0';
			r = Builder.AddSectionFromMemory(name.c_str(), buffer, size);
			TESTLOG(String(buffer).c_str())
			delete buffer;
		}
		else r = -1;

		delete fp;
#else
//		FileInterface::onFileRequest.emit(name);
//		r = Builder.AddSectionFromFile(String(FileInterface::m_root + name).c_str());
		//printf("Adding section from file: %s\n",String(FileInterface::m_root + name).c_str() );
#endif

		if(r<0){
			TESTLOG("Could not stream file data into the Script Module.")
			return 0;
		}

		r = Builder.BuildModule();
		if(r<0){
			TESTLOG("Could not compile the script file.")
			return 0;
		}

		asScript = new ASScript();
		asScript->myParent = this;
		asScript->myModule = asEngine->GetModule(name.c_str());

		if(asScript->myModule == NULL){

			TESTLOG("Module was not created properly.\n")
			return NULL;
		}
	}

	return asScript;
};

/// Loads a precompiled script into the engine
/// Before loading the script, ensure the functionality it uses is exported.
/// \param name The name of the script to load, relative to the executable directory, or the added directories
/// \param alias An override for the name, as the search keyword of this script. Ignored if empty.
/// \return ASScript structure to interact with the loaded script, NULL if failed to load.
ASScript* ASEngine::loadCompiledScript(const String &name, const String &alias){
	ASScript* asScript = NULL;

	//if(myLoade)

	return asScript;
};

/// Get the list of paths for searching scripts
const StringList& ASEngine::getSearchPaths(){
	return mySearchPaths;
};

/// Add a new search path
void ASEngine::addSearchPath(const String &path){
	mySearchPaths.append(path);
};

/// Add a few search paths
void ASEngine::addSearchPaths(const StringList &paths){
	mySearchPaths.append(paths);
};

/// Removes a search path
void ASEngine::removeSearchPath(const String &name){
	mySearchPaths.erase(std::find(mySearchPaths.begin(), mySearchPaths.end(), name) );
};

/// Remove all search paths
void ASEngine::clearSearchPaths(){
	mySearchPaths.clear();
};

/// Reset will reinitialize everything.
void ASEngine::reset(){

};

/// Find your script structure by its name/alias
/// NULL is returned on failure to find it.
/// Do not DELETE this yourself, rather call the appropriate function.
ASScript* ASEngine::findScript(const String &name){
	return NULL;
};


/// Wrapper for exporting reference only data types, that means they cannot be instantiated in scripts.
/// name will be the name to be known from scripts
/// typeSize is just sizeof(MyClassType)
/// dummyMethod must contain the name of a useless method from your class, because of an internal detail.
/// Such as "dummy", if you have a function void dummy() that does nothing .
int ASEngine::exportReferenceDataType(const String &name){
	asEngine->RegisterObjectType(name.c_str(), 0, asOBJ_REF);

	int r;

	if (strstr(asGetLibraryOptions(), "AS_MAX_PORTABILITY")){
		r = asEngine->RegisterObjectBehaviour(name.c_str(), asBEHAVE_ADDREF, "void f()", WRAP_OBJ_LAST(dummy), asCALL_GENERIC); if(r < 0)printf("r %d", r);
		r = asEngine->RegisterObjectBehaviour(name.c_str(), asBEHAVE_RELEASE, "void f()", WRAP_OBJ_LAST(dummy), asCALL_GENERIC); if(r < 0)printf("r %d", r);

	}
	else{
		r = asEngine->RegisterObjectBehaviour(name.c_str(), asBEHAVE_ADDREF, "void f()", asFUNCTION(dummy), asCALL_CDECL_OBJLAST); if(r < 0)printf("r %d", r);
		r = asEngine->RegisterObjectBehaviour(name.c_str(), asBEHAVE_RELEASE, "void f()", asFUNCTION(dummy), asCALL_CDECL_OBJLAST); if(r < 0)printf("r %d", r);
	}

	return r;
};

/// Declare a global property in the scripts
/// Data can be NULL if the type will be instanced by the script
int ASEngine::exportGlobalProperty(const String &declaration, void* data){
	int r = asEngine->RegisterGlobalProperty(declaration.c_str(), data);
	return r;
};

/// Compiles all scripts in the search directories
/// All files found in the directories ending with .sourceextension will be compiled into byte code.
/// \param destExtension Those files will be output with the same name.destExtension
/// \param destDirectory Where to output the file, relative to where the file is. Useful to separate between 32 bit and 64 bit versions
bool ASEngine::compileAllScripts(const String &sourceExtension, const String &destExtension, const String &destDirectory, const String &prefix){

	return false;
};

/// Compiles a script to a destination file.
bool ASEngine::compileScript(const String &scriptName,  const String &destName){
	return false;
};

/// Shortcut to call methods on compiled scripts
/// usage: callScriptMethod("myscript.as", "void main()");
/// And there it goes.
bool ASEngine::callScriptMethod(const String &scriptName, const String &method){
	asIScriptModule *module = asEngine->GetModule(scriptName.c_str());
	if(!module) return false; //not available

	bool Result = true;
	int r;
	int mainId;

	asIScriptContext *context = asEngine->CreateContext();

	r = module->ResetGlobalVars(context);
	if(r < 0) return false;

	//mainId = module->GetFunctionIdByDecl(method.c_str());
	if(mainId < 0){
		std::cout<<"Error: Specified function was not found."<<std::endl;
		return false;
	}

//	context->Prepare(mainId);
	r = context->Execute();
	if(r == asEXECUTION_FINISHED){
		//std::cout<<"Ran sucessfully the script."<<std::endl;
	}
	else{
		//something is wrong
		switch(r){
		case asEXECUTION_ERROR:
			break;

		}
	}

	context->Release();

	return Result;

	return true;
};

////////////////////////////////////////////////////////////////////////// Exportation

/// Forces the basic game core functionality to be exported and sets game a global property, known by varName.
/// You must ensure that the GameCore instance is valid while this engine is running.
/// That shouldn't be a problem if your game owns locally the engine.
bool ASEngine::exportGameAs(const String &varName, GameCore* game){
	if(!gameCoreBasic) return false;
	asEngine->RegisterGlobalProperty(String("GameCore " + varName).c_str(), game);
	return true;
};

/// Exports the most basic functionality of a game, GameCore is always known by reference, and can't be instanced from scripts.
/// Only things like the name() function and other simple things are exported here.
bool ASEngine::exportBasicGameCore(){
	if(gameCoreBasic)return true;
	asEngine->RegisterObjectType("GameCore", sizeof(GameCore), asOBJ_REF);

/*
	int r;
	r = asEngine->RegisterObjectBehaviour("GameCore", asBEHAVE_ADDREF, "void f()", asMETHOD(GameCore,dummy), asCALL_THISCALL); if(r < 0)printf("r %d", r);
	r = asEngine->RegisterObjectBehaviour("GameCore", asBEHAVE_RELEASE, "void f()", asMETHOD(GameCore,dummy), asCALL_THISCALL); if(r < 0)printf("r %d", r);

	r = asEngine->RegisterObjectMethod("GameCore", "string& name()", asMETHOD(GameCore, name) , asCALL_THISCALL);if(r < 0)printf("r %d", r);
	//r = asEngine->RegisterObjectMethod("GameCore", "void runEngineScript(const string& in)", asMETHOD(GameCore, runScript) , asCALL_THISCALL);if(r < 0)printf("r %d", r);
	r = asEngine->RegisterObjectMethod("GameCore", "void close()", asMETHOD(GameCore, close) , asCALL_THISCALL);if(r < 0)printf("r %d", r);
	r = asEngine->RegisterObjectMethod("GameCore", "string& windowTitle()", asMETHOD(GameCore, windowTitle) , asCALL_THISCALL);if(r < 0)printf("r %d", r);
	r = asEngine->RegisterObjectMethod("GameCore", "void setWindowTitle(const string& in)", asMETHOD(GameCore, setWindowTitle) , asCALL_THISCALL);if(r < 0)printf("r %d", r);

	gameCoreBasic = true;*/
	return true;
};

/// Exports audio support from scripts. Only works if a game is known.
bool ASEngine::exportSoundGameCore(){
	if(!gameCoreBasic)return false;
	/*
	asEngine->RegisterObjectType("SoundPlayer", sizeof(SoundPlayer), asOBJ_REF);
	int r;
	r = asEngine->RegisterObjectBehaviour("SoundPlayer", asBEHAVE_ADDREF, "void f()", asMETHOD(SoundPlayer,dummy), asCALL_THISCALL); if(r < 0)printf("r %d", r);
	r = asEngine->RegisterObjectBehaviour("SoundPlayer", asBEHAVE_RELEASE, "void f()", asMETHOD(SoundPlayer,dummy), asCALL_THISCALL); if(r < 0)printf("r %d", r);

	if(exportedContentBanks)
		r = asEngine->RegisterObjectMethod("SoundPlayer", "void setContentBank(ContentBank@)", asMETHOD(SoundPlayer, setContentBank) , asCALL_THISCALL);if(r < 0)printf("r %d", r);
	r = asEngine->RegisterObjectMethod("SoundPlayer", "bool playSound(const string &in)", asMETHOD(SoundPlayer, playSound) , asCALL_THISCALL);if(r < 0)printf("r %d", r);
	r = asEngine->RegisterObjectMethod("SoundPlayer", "bool playMusic(const string &in)", asMETHOD(SoundPlayer, playMusic) , asCALL_THISCALL);if(r < 0)printf("r %d", r);


	r = asEngine->RegisterObjectMethod("GameCore", "SoundPlayer& getSoundPlayer(const string &in)", asMETHOD(GameCore, getSoundPlayer) , asCALL_THISCALL);if(r < 0)printf("r %d", r);
	r = asEngine->RegisterObjectMethod("GameCore", "void removeSoundPlayer(const string &in)", asMETHOD(GameCore, removeSoundPlayer) , asCALL_THISCALL);if(r < 0)printf("r %d", r);
	*/


	//r = asEngine->RegisterObjectMethod("SoundPlayer", "void say(const string &in)", asMETHOD(SoundPlayer, say) , asCALL_THISCALL);if(r < 0)printf("r %d", r);

	gameCoreSound = true;
	return true;
};

/// Exports common script utilities
bool ASEngine::exportBasicScriptInformation(){
	asEngine->RegisterEnum("PlatformType");
/*	asEngine->RegisterEnumValue("PlatformType", "Mobile", ApplicationSettings::Mobile);
	asEngine->RegisterEnumValue("PlatformType", "Desktop", ApplicationSettings::Desktop);

	if (strstr(asGetLibraryOptions(), "AS_MAX_PORTABILITY")){
		asEngine->RegisterGlobalFunction("int getPlatformType()", WRAP_FN(Application::getPlatformType), asCALL_GENERIC);
	}
	else{
		asEngine->RegisterGlobalFunction("int getPlatformType()", asFUNCTION(Application::getPlatformType), asCALL_CDECL);
	}*/

	return false;
};

void Vec2fCTOR(void* memory){
	new(memory) Vec2f();
}
void Vec2fCTOR2(float x, float y, void* memory){
	new(memory) Vec2f(x,y);
}
void Vec2fCCTOR(const Vec2f &in, void* memory){
	new(memory) Vec2f(in);
}
void Vec2fDTOR(void* memory){
	((Vec2f*)memory)->~Vec2f();
}
void Vec2iCTOR(void* memory){
	new(memory) Vec2i();
}
void Vec2iCTOR2(int x, int y, void* memory){
	new(memory) Vec2i(x,y);
}
void Vec2iCCTOR(const Vec2i &in, void* memory){
	new(memory) Vec2i(in);
}
void Vec2iDTOR(void* memory){
	((Vec2i*)memory)->~Vec2i();
}

/// Exports basic functionality and access to the global engine
/// By default, it will be known as Engine, change at will.
bool ASEngine::exportBasicEngine(const String &varName){
	if(engineBasic)return true;

	int r;
	asEngine->RegisterObjectType("Vec2f", sizeof(Vec2f), asOBJ_VALUE | asOBJ_APP_CLASS_CDAK);

	if(getPortableMode()){
		asEngine->RegisterObjectBehaviour("Vec2f", asBEHAVE_CONSTRUCT, "void f()", WRAP_OBJ_LAST(Vec2fCTOR), asCALL_GENERIC);
		asEngine->RegisterObjectBehaviour("Vec2f", asBEHAVE_CONSTRUCT, "void f(float x, float y)", WRAP_OBJ_LAST(Vec2fCTOR2), asCALL_GENERIC);
		asEngine->RegisterObjectBehaviour("Vec2f", asBEHAVE_DESTRUCT, "void f()", WRAP_OBJ_LAST(Vec2fDTOR), asCALL_GENERIC);
		asEngine->RegisterObjectBehaviour("Vec2f", asBEHAVE_CONSTRUCT, "void f(const Vec2f &in)", WRAP_OBJ_LAST(Vec2fCCTOR), asCALL_GENERIC);
		asEngine->RegisterObjectMethod("Vec2f", "Vec2f &opAssign(const Vec2f &in)", WRAP_MFN_PR(Vec2f, operator=, (const Vec2f &), Vec2f&), asCALL_GENERIC);

	}
	else{
		asEngine->RegisterObjectBehaviour("Vec2f", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(Vec2fCTOR), asCALL_CDECL_OBJLAST);
		asEngine->RegisterObjectBehaviour("Vec2f", asBEHAVE_CONSTRUCT, "void f(float x, float y)", asFUNCTION(Vec2fCTOR2), asCALL_CDECL_OBJLAST);
		asEngine->RegisterObjectBehaviour("Vec2f", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(Vec2fDTOR), asCALL_CDECL_OBJLAST);
		asEngine->RegisterObjectBehaviour("Vec2f", asBEHAVE_CONSTRUCT, "void f(const Vec2f &in)", asFUNCTION(Vec2fCCTOR), asCALL_CDECL_OBJLAST);
		asEngine->RegisterObjectMethod("Vec2f", "Vec2f &opAssign(const Vec2f &in)", asMETHODPR(Vec2f, operator=, (const Vec2f &), Vec2f&), asCALL_THISCALL);

	}

	asEngine->RegisterObjectProperty("Vec2f", "float x", asOFFSET(Vec2f, x));
	asEngine->RegisterObjectProperty("Vec2f", "float y", asOFFSET(Vec2f, y));

	asEngine->RegisterObjectType("Vec2i", sizeof(Vec2i), asOBJ_VALUE | asOBJ_APP_CLASS_CDAK);

	if(getPortableMode()){
		asEngine->RegisterObjectBehaviour("Vec2i", asBEHAVE_CONSTRUCT, "void f()", WRAP_OBJ_LAST(Vec2iCTOR), asCALL_GENERIC);
		asEngine->RegisterObjectBehaviour("Vec2i", asBEHAVE_CONSTRUCT, "void f(int x, int y)", WRAP_OBJ_LAST(Vec2iCTOR2), asCALL_GENERIC);
		asEngine->RegisterObjectBehaviour("Vec2i", asBEHAVE_DESTRUCT, "void f()", WRAP_OBJ_LAST(Vec2iDTOR), asCALL_GENERIC);
		asEngine->RegisterObjectBehaviour("Vec2i", asBEHAVE_CONSTRUCT, "void f(const Vec2i &in)", WRAP_OBJ_LAST(Vec2iCCTOR), asCALL_GENERIC);
		asEngine->RegisterObjectMethod("Vec2i", "Vec2i &opAssign(const Vec2i &in)", WRAP_MFN_PR(Vec2i, operator=, (const Vec2i &), Vec2i&), asCALL_GENERIC);

	}
	else{
		asEngine->RegisterObjectBehaviour("Vec2i", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(Vec2iCTOR), asCALL_CDECL_OBJLAST);
		asEngine->RegisterObjectBehaviour("Vec2i", asBEHAVE_CONSTRUCT, "void f(int x, int y)", asFUNCTION(Vec2iCTOR2), asCALL_CDECL_OBJLAST);
		asEngine->RegisterObjectBehaviour("Vec2i", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(Vec2iDTOR), asCALL_CDECL_OBJLAST);
		asEngine->RegisterObjectBehaviour("Vec2i", asBEHAVE_CONSTRUCT, "void f(const Vec2i &in)", asFUNCTION(Vec2iCCTOR), asCALL_CDECL_OBJLAST);
		asEngine->RegisterObjectMethod("Vec2i", "Vec2i &opAssign(const Vec2i &in)", asMETHODPR(Vec2i, operator=, (const Vec2i &), Vec2i&), asCALL_THISCALL);

	}

	asEngine->RegisterObjectProperty("Vec2i", "int x", asOFFSET(Vec2i, x));
	asEngine->RegisterObjectProperty("Vec2i", "int y", asOFFSET(Vec2i, y));


	exportReferenceDataType("Window");

	//r = asEngine->RegisterObjectMethod("Window", "Vec2f getGameName(int)", asMETHOD(Engine, as_gameNameAt) , asCALL_THISCALL);if(r < 0)printf("r %d", r);
	/*


	asEngine->RegisterObjectType("EngineSDK", sizeof(Engine), asOBJ_REF);

	r = asEngine->RegisterObjectBehaviour("EngineSDK", asBEHAVE_ADDREF, "void f()", asMETHOD(Engine,dummy), asCALL_THISCALL); if(r < 0)printf("r %d", r);
	r = asEngine->RegisterObjectBehaviour("EngineSDK", asBEHAVE_RELEASE, "void f()", asMETHOD(Engine,dummy), asCALL_THISCALL); if(r < 0)printf("r %d", r);

	r = asEngine->RegisterObjectMethod("EngineSDK", "string getGameName(int)", asMETHOD(Engine, as_gameNameAt) , asCALL_THISCALL);if(r < 0)printf("r %d", r);
	r = asEngine->RegisterObjectMethod("EngineSDK", "int gameCount()", asMETHOD(Engine, as_gameCount) , asCALL_THISCALL);if(r < 0)printf("r %d", r);
	r = asEngine->RegisterObjectMethod("EngineSDK", "void loadGame(const string &in, const string &in)", asMETHOD(Engine, as_createScriptGame) , asCALL_THISCALL);if(r < 0)printf("r %d", r);
	r = asEngine->RegisterObjectMethod("EngineSDK", "Window@ getWindow()", asMETHOD(Engine, getWindow) , asCALL_THISCALL);if(r < 0)printf("r %d", r);

	asEngine->RegisterGlobalProperty(String(String("EngineSDK ") + varName).c_str(), Engine::instance());


	*/

	engineBasic = true;
	return engineBasic;
};

void testP()
{

}

/// Exports string functionality
bool ASEngine::exportStrings(){
	if(!asEngine)return false;

	RegisterStdString(asEngine);
	RegisterScriptArray(asEngine, false);
	RegisterStdStringUtils(asEngine);

	int r;

	if (strstr(asGetLibraryOptions(), "AS_MAX_PORTABILITY")){
		r = asEngine->RegisterGlobalFunction("void print(string)", WRAP_FN(scriptstdprint), asCALL_GENERIC);
		if(r < 0){
			TESTLOG("FAILED TO REGISTER print(string)\n")
		}
	}
	else
	{
		r = asEngine->RegisterGlobalFunction("void print(string)", asFUNCTION(scriptstdprint), asCALL_CDECL);
		r = asEngine->RegisterGlobalFunction("void testP()", asFUNCTION(testP), asCALL_CDECL);
		if(r < 0){
			//pLogger::Log(LogLevel::Critical, "Failed to export a function.");
		}
	}

	return true;
};

/// Exports file support
bool ASEngine::exportFiles(){
	RegisterScriptFile(asEngine);
	return true;
};

/// Exports math support
bool ASEngine::exportMath(){
	RegisterScriptMath(asEngine);
	return true;
};


NEPHILIM_NS_END
