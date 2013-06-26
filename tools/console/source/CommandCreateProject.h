#ifndef CommandCreateProject_h__
#define CommandCreateProject_h__

#include "Command.h"
#include "Utility.h"

#include <Nephilim/FileSystem.h>
using namespace NEPHILIM_NS;

class CommandCreateProject : public NativeCommand
{
	void execute(String command);
};

#endif // CommandCreateProject_h__
