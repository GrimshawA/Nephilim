#ifndef ProgramContext_h__
#define ProgramContext_h__

#include "Command.h"

#include <Nephilim/Strings.h>
using namespace NEPHILIM_NS;

#include <vector>
#include <map>

class Info
{
public:
	static void init();

	static String assetPath;

	static NativeCommand* getCommand(const String& name);

	static std::map<String, NativeCommand*> nativeActions; 

};

#endif // ProgramContext_h__
