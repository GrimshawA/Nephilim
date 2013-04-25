#ifndef ASXRuntime_h__
#define ASXRuntime_h__

#include "Platform.h"

class asIScriptContext;

NEPHILIM_NS_BEGIN

class ASXEngine;
class ASXModule;

class NEPHILIM_API ASXRuntime
{
public:
	ASXRuntime();

	ASXRuntime(ASXEngine& engine);

	~ASXRuntime();

	asIScriptContext* get();

	void pushState();
	void popState();

	void set(ASXEngine& engine);

	/// Resets the global variables of a module in this runtime context
	void reset(ASXModule& module);

private:
	asIScriptContext* m_context;
};

NEPHILIM_NS_END
#endif // ASXRuntime_h__
