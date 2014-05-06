#include <Nephilim/ASXRuntime.h>
#include <Nephilim/ASXEngine.h>

#include <angelscript.h>

NEPHILIM_NS_BEGIN

ASXRuntime::ASXRuntime()
: m_context(NULL)
{

}

ASXRuntime::ASXRuntime(ASXEngine& engine)
{
	m_context = engine.get()->CreateContext();
}

ASXRuntime::~ASXRuntime()
{
	if(m_context) m_context->Release();
}

asIScriptContext* ASXRuntime::get()
{
	return m_context;
}

void ASXRuntime::pushState()
{
	if(m_context) m_context->PushState();
}

void ASXRuntime::popState()
{
	if(m_context) m_context->PopState();
}

void ASXRuntime::set(ASXEngine& engine)
{
	m_context = engine.get()->CreateContext();
}

void ASXRuntime::reset(ASXModule& module)
{
	if(m_context)
	{
		module.get()->ResetGlobalVars(m_context);
	}
}

NEPHILIM_NS_END