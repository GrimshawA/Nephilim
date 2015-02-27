#ifndef NephilimFoundationScript_h__
#define NephilimFoundationScript_h__

#include <Nephilim/Foundation/Asset.h>

NEPHILIM_NS_BEGIN

/**
	\class Script
	\brief Base class for all scripts from any language

	This is only an interface and defines no functionality,
	it serves as base class for any logic that is executed
	outside of the c++ domain, whether its Lua, AngelScript,
	C# or anything else. 

	Usually each script object contains bytecode or any other
	form of executable code, in its respective language.
*/
class NEPHILIM_API Script : public Asset
{
public:


};

NEPHILIM_NS_END
#endif // NephilimFoundationScript_h__
