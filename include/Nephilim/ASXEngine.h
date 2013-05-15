#ifndef ASXEngine_h__
#define ASXEngine_h__

#include "Platform.h"
#include "ASXModule.h"
#include "ASXRuntime.h"
#include "ASXFunction.h"

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

	/// Load a script
//	bool load(const String& path);
	
private:
	/// The logger bound to the engine
	void messageLogger(const asSMessageInfo *msg, void *param);

private:
	asIScriptEngine* m_engine;   ///< The AngelScript engine
	bool			 m_generics; ///< Whether the engine is using generics or native calls
};

NEPHILIM_NS_END
#endif // ASXEngine_h__
