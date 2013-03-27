#ifndef PARABOLA_ANGELSCRIPTING_H
#define PARABOLA_ANGELSCRIPTING_H

#include "Platform.h"
#include "Strings.h"
#include "StringList.h"
#include "ASScript.h"
#include "NameGenerator.h"
#include "angelscript.h"

#include <map>
#include <vector>

#include <iostream>
using namespace std;

PARABOLA_NAMESPACE_BEGIN

class GameCore;
class ParticleSystem;
class RocketDocument;

/// Namespace contains profiles that can be set directly.
namespace ScriptProfiles{
	enum Profiles{
		None = 0,
		Custom,
		MainGame,
		UserInterface,
		Scene,
		Entity,
		AI
	};
};

template<typename T>
void ObjectCopyConstructor(const T &in, void* address){
	new(address) T(in);
}

template<typename T>
void constructObject(void* address){
	new(address) T();
}

template<typename T>
T* genericFactory()
{
	//cout<<"instancing ref type"<<endl;
	return new T();
}

// Example REF_CAST behaviour
template<class A, class B>
B* refCast(A* a)
{
	/*// If the handle already is a null handle, then just return the null handle
	if( !a ) return 0;
	// Now try to dynamically cast the pointer to the wanted type
	B* b = dynamic_cast<B*>(a);
	if( b != 0 )
	{
		// Since the cast was made, we need to increase the ref counter for the returned handle
		b->addReference();
	}
	return b;*/
	B* b = static_cast<B*>(a);
	//b->addReference();
	return b;
}
/**
	\ingroup Scripting
	\class ASEngine
	\brief Represents an interface with AngelScript

	It allows you to compile and execute scripts, among other interactions.

	Each instance of this class is a completely different AngelScript context,
	nothing is exported by default, and you may export functionality at taste,
	to differentiate possible types of scripts.

	For example, and the common use, you will have an AngelScript engine for your
	GameCore instance, which will be able to manage the game, and its events.

	Then, you will have an ASEngine for all entities, or all enemies, 
	however you need it done. That engine will only export stuff specific of entities,
	both to protect abuse from within the scripts, and to give a better interface to it.

	Eventually, if you want a game that can be modded via scripts, you can actually limit
	what the modders can do..

	--

	You get plenty of export functions you can use, each one will export a set of functionality to the
	scripts of this instance. They all load automatically their dependencies, if you didn't do it before.

	Also, some export functions may need to receive data to function right, such as the one that provides you
	access to your game.
*/
class PARABOLA_API ASEngine{
public:
	/// Creates an empty but ready angel script engine
	ASEngine();

	/// Ensures proper destruction of the engine
	virtual ~ASEngine();

	/// Returns the pointer to the internal angel script engine
	/// Possible use could be to export functions.
	asIScriptEngine* getASEngine();

	/// Destroys a script from the engine
	void unloadScript(const String &name);

	/// Reset will reinitialize everything.
	void reset();

	/// Loads a script from a null terminated char buffer
	ASScript* loadScriptFromMemory(const char* buffer, const String &scriptName);

	/// Loads a script into the engine
	/// Any functionality the script requires must be exported before loading it
	/// \param name The name of the script to load, relative to the executable directory, or the added directories
	/// \param alias An override for the name, as the search keyword of this script. Ignored if empty.
	/// \param isByteCode When true, the script is assumed to be already compiled, and is loaded as bytecode. 
	/// \return ASScript structure to interact with the loaded script, NULL if failed to load.
	/////////////////////////////////////////////////////////////////////////////////////////////////
	ASScript* loadScript(const String &name, const String &alias = "", bool isByteCode = false);

	/// Loads a precompiled script into the engine
	/// Before loading the script, ensure the functionality it uses is exported.
	/// \param name The name of the script to load, relative to the executable directory, or the added directories
	/// \param alias An override for the name, as the search keyword of this script. Ignored if empty.
	/// \return ASScript structure to interact with the loaded script, NULL if failed to load.
	ASScript* loadCompiledScript(const String &name, const String &alias = "");

	/// Get the list of paths for searching scripts
	const StringList& getSearchPaths();

	/// Returns true if compiling in the max compatibility profile, for mobile devices etc
	bool getPortableMode();

	/// Add a new search path
	void addSearchPath(const String &path);

	/// Add a few search paths
	void addSearchPaths(const StringList &paths);

	/// Removes a search path
	void removeSearchPath(const String &name);

	/// Remove all search paths
	void clearSearchPaths();

	/// Find your script structure by its name/alias
	/// NULL is returned on failure to find it.
	/// Do not DELETE this yourself, rather call the appropriate function.
	ASScript* findScript(const String &name);

	/// Export a type as reference, that means it can only be instanced through C++
	int exportReferenceDataType(const String &name);

	/// Declare a global property in the scripts
	/// Data can be NULL if the type will be instanced by the script
	int exportGlobalProperty(const String &declaration, void* data);

	/// Compiles all scripts in the search directories
	/// All files found in the directories ending with .sourceextension will be compiled into byte code.
	/// \param destExtension Those files will be output with the same name.destExtension
	/// \param destDirectory Where to output the file, relative to where the file is. Useful to separate between 32 bit and 64 bit versions
	bool compileAllScripts(const String &sourceExtension, const String &destExtension, const String &destDirectory = ".", const String &prefix = "");

	/// Compiles a script to a destination file.
	bool compileScript(const String &scriptName,  const String &destName);

	/// Shortcut to call methods on compiled scripts
	/// usage: callScriptMethod("myscript.as", "void main()");
	/// And there it goes.
	bool callScriptMethod(const String &scriptName, const String &method);

	////////////////////////////////////////////////////////////////////////// Exportation

	/// Forces the basic game core functionality to be exported and sets game a global property, known by varName.
	/// You must ensure that the GameCore instance is valid while this engine is running.
	/// That shouldn't be a problem if your game owns locally the engine.
	bool exportGameAs(const String &varName, GameCore* game);

	/// Exports the most basic functionality of a game, GameCore is always known by reference, and can't be instanced from scripts.
	/// Only things like the name() function and other simple things are exported here.
	bool exportBasicGameCore();

	/// Exports audio support from scripts. Only works if a game is known.
	bool exportSoundGameCore();

	/// Exports common script utilities
	bool exportBasicScriptInformation();

	/// Exports basic functionality and access to the global engine
	/// By default, it will be known as Engine, change at will.
	bool exportBasicEngine(const String &varName = "SDK");

	/// Exports string functionality
	bool exportStrings();

	/// Exports file support
	bool exportFiles();

	/// Exports math support
	bool exportMath();

	/// Exports events as a reference type
	bool exportEvents();

	/// Exports physics functionality
	bool exportKinesis();
	
	/// Exports the renderer and a few more things
	bool exportGraphics();

	/// Exports the content banks
	bool exportContentBanks();

	/// Exports access to rocket ui
	bool exportRocketUi();

	/// Exports as rocket scripting tools
	bool exportRocketScripting(RocketDocument* document);

	/// Exports animation support
	bool exportAnimations();

	/// Exports support for particle effects(systems), usage and not specification of them
	bool exportParticleSystems();

	//////////////////////////////////////////////////////////////////////////

	/// Exports everything necessary to make this engine a particle loader
	void activateParticleLoaderProfile();

	////////////////////////////////////////////////////////////////////////// Static utilities
	
	/// Prepares an AS engine with particle systems support, creates one system and returns it
	static ParticleSystem* loadParticleSystem(const String &scriptName, ParticleSystem *pSystem = NULL, bool byteCode = false);

private:
	/// AngelScript engine 1:1 with this class
	asIScriptEngine* asEngine;

	/// Holds a reference to all loaded (compiled) scripts.
	/// The Key Value string can be an alias.
	std::map<String, ASScript*> myLoadedScripts;

	/// All paths that can be searched for files
	/// By default contains only the empty string, or the . directory
	StringList mySearchPaths;

	/// Exported functionality booleans
	bool gameCoreBasic;
	bool gameCoreAdvanced;
	bool gameCoreSound;
	bool gameCoreExported;
	bool scriptBasic;
	bool engineBasic;
	bool exportedParticles;
	bool exportedKinesis;
	bool exportedRenderer;
	bool exportedContentBanks;
	bool exportedRocket;
	bool exportedRocketInternal;

	/// Profile
	ScriptProfiles::Profiles myScriptingProfile;
};
PARABOLA_NAMESPACE_END
#endif