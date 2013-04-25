#include <Nephilim/ASXEngine.h>
#include <Nephilim/Logger.h>

#include <AS/angelscript.h>
#include <AS/aswrappedcall.h>
#include <AS/scriptbuilder.h>

#include <string.h>

NEPHILIM_NS_BEGIN

	static void ASSLOG(const asSMessageInfo *msg, void *param){
		if(!msg)return;
		const char *type = "ERR ";
		if( msg->type == asMSGTYPE_WARNING )
			type = "WARN";
		else if( msg->type == asMSGTYPE_INFORMATION )
			type = "INFO";

		//printf("%s (%d, %d) : %s : %s\n", msg->section, msg->row, msg->col, type, msg->message);
		PRINTLOG("AngelScript", "%s (%d, %d) : %s : %s\n", msg->section, msg->row, msg->col, type, msg->message)

};
ASXEngine::ASXEngine()
: m_generics(false)
, m_engine(NULL)
{
	m_engine = asCreateScriptEngine(ANGELSCRIPT_VERSION);
	if(m_engine)
	{
		m_generics = static_cast<bool>(strlen(strstr(asGetLibraryOptions(), "AS_MAX_PORTABILITY")) > 0);

		//m_engine->SetMessageCallback(WRAP_MFN(ASXEngine, messageLogger), this, asCALL_GENERIC);
		m_engine->SetMessageCallback(asFUNCTION(ASSLOG), 0, asCALL_CDECL);
		m_engine->SetEngineProperty(asEP_INIT_GLOBAL_VARS_AFTER_BUILD, false);
	}
}


ASXEngine::~ASXEngine()
{
	if(m_engine) m_engine->Release();
}

/// Get the angel script engine or NULL if it failed
asIScriptEngine* ASXEngine::get() const
{
	return m_engine;
}

/// Returns true if AngelScript is in the maximum compatibility mode - generic calls
bool ASXEngine::getCompatibilityMode()
{
	return m_generics;
}

/// The logger bound to the engine
void ASXEngine::messageLogger(const asSMessageInfo *msg, void *param)
{
	if(!msg)return;
	const char *type = "ERR ";
	if( msg->type == asMSGTYPE_WARNING )
		type = "WARN";
	else if( msg->type == asMSGTYPE_INFORMATION )
		type = "INFO";

	//printf("%s (%d, %d) : %s : %s\n", msg->section, msg->row, msg->col, type, msg->message);
	PRINTLOG("AngelScript", "%s (%d, %d) : %s : %s\n", msg->section, msg->row, msg->col, type, msg->message)
}

NEPHILIM_NS_END