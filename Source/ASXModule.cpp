#include <Nephilim/ASXModule.h>
#include <Nephilim/ASXEngine.h>

#include <AS/scriptbuilder.h>

NEPHILIM_NS_BEGIN

ASXModule::ASXModule()
: m_module(NULL)
{

}

ASXModule::ASXModule(asIScriptModule* module)
{
	m_module = module;
}

asIScriptModule* ASXModule::get()
{
	return m_module;
}


ASXModule::operator bool()
{
	return m_module != NULL;
}


//////////////////////////////////////////////////////////////////////////

ASXModuleBuilder::ASXModuleBuilder()
: m_builder(NULL)
{

}

ASXModuleBuilder::ASXModuleBuilder(const ASXEngine& scriptEngine, const String& moduleName)
{
	m_builder = new CScriptBuilder();
	m_builder->StartNewModule(scriptEngine.get(), moduleName.c_str());
	m_module = m_builder->GetModule();
}

ASXModuleBuilder::~ASXModuleBuilder()
{
	delete m_builder;
}

void ASXModuleBuilder::create(const ASXEngine& scriptEngine, const String& moduleName)
{

}

void ASXModuleBuilder::clear()
{

}

ASXModule ASXModuleBuilder::build()
{
	if(m_builder)
	{
		m_builder->BuildModule();
	}
	ASXModule module(m_module);
	return module;
}

bool ASXModuleBuilder::addSourceFile(const String& filename)
{
	return true;
}

void ASXModuleBuilder::addSource(const String& source)
{
	m_builder->AddSectionFromMemory("fragment", source.c_str());
}

bool ASXModuleBuilder::addBytecodeFile(const String& filename)
{
	return true;
}

void ASXModuleBuilder::addBytecode(const String& code)
{

}

void ASXModuleBuilder::setPreprocessorEnabled(bool enable)
{

}


//////////////////////////////////////////////////////////////////////////


ASXModuleWriter::ASXModuleWriter(ASXModule& module)
: m_module(&module)
{

}

bool ASXModuleWriter::save(const String& path)
{
	return true;
}

NEPHILIM_NS_END