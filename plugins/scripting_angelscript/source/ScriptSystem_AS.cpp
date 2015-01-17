#include "ScriptSystem_AS.h"
#include "ScriptingEnvironment_AS.h"

#include <Nephilim/Logger.h>

#include <Nephilim/World/Actor.h>

#include <Nephilim/Game/GameMessage.h>


// Registration
#include <Nephilim/ASX/ASXRegistrationVectors.h>
#include <Nephilim/ASX/ASXRegistrationKeyboard.h>


void dummy(void* obj)
{

}

void GameMessageCTOR(void* memory)
{
	new (memory) GameMessage();
}

void GameMessageKTOR(const GameMessage& m, void* memory)
{
	new (memory) GameMessage(m);
}

void GameMessageDTOR(void* memory)
{
	((GameMessage*)memory)->~GameMessage();
}

void RegisterGameMessage(ASXEngine& engine)
{
	engine.get()->RegisterObjectType("GameMessage", sizeof(GameMessage), asOBJ_VALUE | asOBJ_APP_CLASS_CDAK);
	engine.get()->RegisterObjectBehaviour("GameMessage", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(GameMessageCTOR), asCALL_CDECL_OBJLAST);
	engine.get()->RegisterObjectBehaviour("GameMessage", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(GameMessageDTOR), asCALL_CDECL_OBJLAST);
	engine.get()->RegisterObjectBehaviour("GameMessage", asBEHAVE_CONSTRUCT, "void f(GameMessage &in)", asFUNCTION(GameMessageKTOR), asCALL_CDECL_OBJLAST);
	engine.get()->RegisterObjectMethod("GameMessage", "GameMessage &opAssign(const GameMessage &in)", asMETHODPR(GameMessage, operator=, (const GameMessage &), GameMessage&), asCALL_THISCALL);

	engine.get()->RegisterObjectProperty("GameMessage", "string t", asOFFSET(GameMessage, temp));
}

void RegisterGameInput(ASXEngine& engine)
{
	engine.get()->RegisterObjectType("GameInput", sizeof(GameInput), asOBJ_REF);
	engine.get()->RegisterObjectBehaviour("GameInput", asBEHAVE_ADDREF, "void f()", asFUNCTION(dummy), asCALL_CDECL_OBJLAST);
	engine.get()->RegisterObjectBehaviour("GameInput", asBEHAVE_RELEASE, "void f()", asFUNCTION(dummy), asCALL_CDECL_OBJLAST);

	engine.get()->RegisterObjectMethod("GameInput", "bool getKeyPressed(int)", asMETHOD(GameInput, getKey), asCALL_THISCALL);
}

void RegisterGameCore(ASXEngine& engine)
{
	RegisterGameInput(engine);

	engine.get()->RegisterObjectType("GameCore", sizeof(GameCore), asOBJ_REF);
	engine.get()->RegisterObjectBehaviour("GameCore", asBEHAVE_ADDREF, "void f()", asFUNCTION(dummy), asCALL_CDECL_OBJLAST);
	engine.get()->RegisterObjectBehaviour("GameCore", asBEHAVE_RELEASE, "void f()", asFUNCTION(dummy), asCALL_CDECL_OBJLAST);

	engine.get()->RegisterObjectMethod("GameCore", "void dispatchMessage(const GameMessage &in)", asMETHOD(GameCore, broadcastMessage), asCALL_THISCALL);
	engine.get()->RegisterObjectMethod("GameCore", "World@ getWorld()", asMETHOD(GameCore, getWorld), asCALL_THISCALL);
	//_env->engine.get()->RegisterObjectMethod("GameCore", "float X()", asMETHOD(Actor, X), asCALL_THISCALL);

	engine.get()->RegisterObjectProperty("GameCore", "GameInput input", asOFFSET(GameCore, gameInput));
}

void RegisterWorlds(ASXEngine& engine)
{
	engine.get()->RegisterObjectType("World", sizeof(World), asOBJ_REF);
	engine.get()->RegisterObjectBehaviour("World", asBEHAVE_ADDREF, "void f()", asFUNCTION(dummy), asCALL_CDECL_OBJLAST);
	engine.get()->RegisterObjectBehaviour("World", asBEHAVE_RELEASE, "void f()", asFUNCTION(dummy), asCALL_CDECL_OBJLAST);

	engine.get()->RegisterObjectMethod("World", "Actor@ getActorByName(const string& in)", asMETHOD(World, getActorByName), asCALL_THISCALL);
	engine.get()->RegisterObjectMethod("World", "int getActorCount()", asMETHOD(World, getActorCount), asCALL_THISCALL);
	
	engine.get()->RegisterObjectProperty("World", "string name", asOFFSET(World, name));
}

/// Prepare the scripting system to function with Nephilim
ScriptSystem_AS::ScriptSystem_AS(ScriptingEnvironment_AS* env)
: _env(env)
{
//	RegisterStdString(env->engine.get());
	//RegisterStdStringUtils(env->engine.get());

	registerVectorsASX(_env->engine);
	registerKeyboardASX(_env->engine);

	
	_env->engine.get()->RegisterObjectType("Actor", sizeof(Actor), asOBJ_REF);
	_env->engine.get()->RegisterObjectBehaviour("Actor", asBEHAVE_ADDREF, "void f()", asFUNCTION(dummy), asCALL_CDECL_OBJLAST);
	_env->engine.get()->RegisterObjectBehaviour("Actor", asBEHAVE_RELEASE, "void f()", asFUNCTION(dummy), asCALL_CDECL_OBJLAST);

	_env->engine.get()->RegisterObjectMethod("Actor", "vec3 getActorLocation()", asMETHOD(Actor, getActorLocation), asCALL_THISCALL);
	_env->engine.get()->RegisterObjectMethod("Actor", "void setActorLocation(vec3)", asMETHOD(Actor, setActorLocation), asCALL_THISCALL);

	RegisterWorlds(_env->engine);

	RegisterGameMessage(_env->engine);
	RegisterGameCore(_env->engine);

	static float FrameTime = 1.f / 30.f;

	_env->engine.get()->RegisterGlobalProperty("GameCore game", env->_game);
	_env->engine.get()->RegisterGlobalProperty("float FrameTime", &FrameTime);
}

void ScriptSystem_AS::testFunction()
{
	Log("Testing functionality");

	ASXEngine engine;
	ASXModule myModule;
	ASXRuntime myRuntime(engine);

	ASXModuleBuilder builder;
	builder.load(engine, "scriptone.as", "test");
	myModule = engine.getModule("test");

	if (myModule)
	{
		Log("COMPILED SUCCESSFULLY");

		ASXFunction func;
		func.mFunction = myModule.get()->GetFunctionByDecl("void printFunc()");
		func.mRuntime = &myRuntime;
		func.call();
	}
}

void ScriptSystem_AS::registerFunction(const String& signature, void* funcPtr)
{
	_env->engine.get()->RegisterGlobalFunction(signature.c_str(), asFUNCTION(funcPtr), asCALL_CDECL);
}

#include <AS/add_on/scriptbuilder/scriptbuilder.h>

IScript* ScriptSystem_AS::compile(const String& filename)
{
	ScriptModuleASX* script = new ScriptModuleASX;
	
	String actorInjectionCode = "class ActorBehavior{ Actor@ _actor = null; Actor@ GetActor(){ return @_actor;} }";
	actorInjectionCode += "class GameBehavior{ }";

	CScriptBuilder as_builder;
	as_builder.StartNewModule(_env->engine.get(), filename.c_str());
	as_builder.AddSectionFromMemory("actorinjection", actorInjectionCode.c_str());
	as_builder.AddSectionFromFile(filename.c_str());
	as_builder.BuildModule();

	script->myModule = _env->engine.getModule(filename.c_str());
	script->_engine = &_env->engine;

	return script;
}

void ScriptSystem_AS::execute(const String& source)
{
	Log("NOPE");
}

//////////////////////////////////////////////////////////////////////////

void ScriptModuleASX::call(const String& funcName)
{
//	Log("Calling script function");

	if (myModule)
	{
		ASXRuntime myRuntime(*_engine);

		ASXFunction func;
		func.mFunction = myModule.get()->GetFunctionByDecl(funcName.c_str());
		func.mRuntime = &myRuntime;
		func.call();
	}
}

void ScriptModuleASX::callOnObject(const String& function_name, void* obj)
{
	if (myModule && obj)
	{
		ASXRuntime myRuntime(*_engine);

		asIObjectType* ObjectType = static_cast<asIScriptObject*>(obj)->GetObjectType();

		ASXFunction func;
		func.mFunction = ObjectType->GetMethodByDecl(function_name.c_str());
		func.mRuntime = &myRuntime;
		func.callOnObject(obj);

		//Log("Calling method '%s' on obj %x", function_name.c_str(), obj);
	}
}

void ScriptModuleASX::setMemberRef(const String& identifier, void* obj, void* ref)
{
	Actor* actorPtr = static_cast<Actor*>(ref);

	if (obj)
	{
		Log("Trying to set a member");

		asIObjectType* ObjectType = static_cast<asIScriptObject*>(obj)->GetObjectType();
		asIScriptObject* Object = static_cast<asIScriptObject*>(obj);

		std::size_t propertyIndex = 0;
		for (auto i = 0; i < Object->GetPropertyCount(); ++i)
		{
			Log("Testing %s", Object->GetPropertyName(i));

			if (String(Object->GetPropertyName(i)) == "_actor")
			{
				propertyIndex = i;
			}
		}

		void* actorProperty = Object->GetAddressOfProperty(propertyIndex);
		if (actorProperty)
		{
			Actor** actor_property = static_cast<Actor**>(actorProperty);
			*actor_property = nullptr;
			*actor_property = actorPtr;

			Log(" ==> Binding actor to behavior. _actor is now %x. Ref was %x", actorProperty, ref);
		}
	}
}

void* ScriptModuleASX::createClassInstance(const String& className)
{
	// Get the object type
	asIScriptModule *module = myModule.get();

	asIObjectType *type = _engine->get()->GetObjectTypeById(module->GetTypeIdByDecl(className.c_str()));

	// Get the factory function from the object type
	asIScriptFunction *factory = type->GetFactoryByDecl((className + " @" + className + "()").c_str());

	ASXRuntime myRuntime(*_engine);

	// Prepare the context to call the factory function
	myRuntime.get()->Prepare(factory);

	// Execute the call
	myRuntime.get()->Execute();

	// Get the object that was created
	asIScriptObject *obj = *(asIScriptObject**)myRuntime.get()->GetAddressOfReturnValue();

	// If you're going to store the object you must increase the reference,
	// otherwise it will be destroyed when the context is reused or destroyed.
	obj->AddRef();

	return obj;
}