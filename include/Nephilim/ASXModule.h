#ifndef ASXModule_h__
#define ASXModule_h__

#include "Platform.h"
#include "Strings.h"

class CScriptBuilder;
class asIScriptModule;

NEPHILIM_NS_BEGIN

class ASXEngine;

/**
	\ingroup Scripting
	\class ASXModule
	\brief Reference to a script module.

	Can be copied around without problems. 
	Beware, when requesting destruction of an ASXModule, all other references become invalid.
*/
class NEPHILIM_API ASXModule
{
public:
	ASXModule();

	ASXModule(asIScriptModule* module);

	asIScriptModule* get();

	operator bool();

private:
	asIScriptModule* m_module;
};

class NEPHILIM_API ASXModuleBuilder
{
public:
	ASXModuleBuilder();

	ASXModuleBuilder(const ASXEngine& scriptEngine, const String& moduleName);

	~ASXModuleBuilder();

	void create(const ASXEngine& scriptEngine, const String& moduleName);

	void clear();

	ASXModule build();

	bool addSourceFile(const String& filename);

	void addSource(const String& source);

	bool addBytecodeFile(const String& filename);

	void addBytecode(const String& code);

	void setPreprocessorEnabled(bool enable);

private:
	bool m_preprocessor;
	CScriptBuilder* m_builder;
	asIScriptModule* m_module;
};

/**
	\ingroup Scripting
	\class ASXModuleWriter
	\brief Takes an ASXModule and writes the compiled byte code to a stream
*/
class NEPHILIM_API ASXModuleWriter
{
public:
	ASXModuleWriter(ASXModule& module);

	bool save(const String& path);

private:
	ASXModule* m_module;
};

NEPHILIM_NS_END
#endif // ASXModule_h__
