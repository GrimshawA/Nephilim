#ifndef NephilimASXModuleBuilder_h__
#define NephilimASXModuleBuilder_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Strings.h>

NEPHILIM_NS_BEGIN

class ASXEngine;

class NEPHILIM_API ASXModuleBuilder
{
public:

	bool load(ASXEngine& engine, const String& filename, const String& module);
};

NEPHILIM_NS_END
#endif // NephilimASXModuleBuilder_h__
