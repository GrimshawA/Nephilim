#ifndef ASXEngine_h__
#define ASXEngine_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Strings.h>
#include "ASXModule.h"

#include <angelscript.h>

#include <Nephilim/ASX/ASXRefCount.h>

struct asSMessageInfo;
class asIScriptEngine;

NEPHILIM_NS_BEGIN

class NEPHILIM_API ASXEngine
{
public:
	/// Constructs angel script
	ASXEngine();

	/// Destructs angel script
	~ASXEngine();

	/// Get the angel script engine or NULL if it failed
	asIScriptEngine* get() const;

	/// Returns true if AngelScript is in the maximum compatibility mode - generic calls
	bool getCompatibilityMode();

	ASXModule getModule(const String& name);

	/// Register a reference type automatically (must be a child of ASXRefCount)
	template<class T>
	void registerClassRef(const String& name);

	/// Load a script
//	bool load(const String& path);
	
private:
	/// The logger bound to the engine
	//void messageLogger(const asSMessageInfo *msg, void *param);

private:
	asIScriptEngine* m_engine;   ///< The AngelScript engine
	bool			 m_generics; ///< Whether the engine is using generics or native calls
};


template<class T>
void ASXEngine::registerClassRef(const String& name)
{
	if(m_engine)
	{
		m_engine->RegisterObjectType(name.c_str(), sizeof(T), asOBJ_REF);

		m_engine->RegisterObjectBehaviour(name.c_str(), asBEHAVE_FACTORY, (name + "@ f()").c_str(), asFUNCTION(ASXRefCount::instance<T>), asCALL_CDECL);
		m_engine->RegisterObjectBehaviour(name.c_str(), asBEHAVE_ADDREF, "void f()", asFUNCTION(ASXRefCount::addRef), asCALL_CDECL_OBJLAST);
		m_engine->RegisterObjectBehaviour(name.c_str(), asBEHAVE_RELEASE, "void f()", asFUNCTION(ASXRefCount::releaseRef), asCALL_CDECL_OBJLAST);
	}
}

NEPHILIM_NS_END
#endif // ASXEngine_h__
