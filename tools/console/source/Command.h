#ifndef Command_h__
#define Command_h__

#include <Nephilim/Strings.h>
#include "ProgramContext.h"

using namespace NEPHILIM_NS;

class NativeCommand
{
public:
	virtual void execute(String command)
	{

	}
};

#endif // Command_h__
