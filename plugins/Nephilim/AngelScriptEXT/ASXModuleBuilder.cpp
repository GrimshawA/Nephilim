#include <Nephilim/AngelScriptEXT/ASXModuleBuilder.h>
#include <Nephilim/AngelScriptEXT/ASXEngine.h>
#include <Nephilim/Foundation/Logging.h>

#include <AS/add_on/scriptbuilder/scriptbuilder.h>

NEPHILIM_NS_BEGIN

bool ASXModuleBuilder::load(ASXEngine& engine, const String& filename, const String& module)
{
	CScriptBuilder builder;
	builder.StartNewModule(engine.get(), module.c_str());
	builder.AddSectionFromFile(filename.c_str());
	if(builder.BuildModule() > 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

NEPHILIM_NS_END
