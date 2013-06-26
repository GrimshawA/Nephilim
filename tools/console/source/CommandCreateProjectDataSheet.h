#ifndef CommandCreateProjectDataSheet_h__
#define CommandCreateProjectDataSheet_h__

#include "Command.h"
#include "Info.h"
#include "Utility.h"

#include <iostream>
using namespace std;

#include <Nephilim/FileSystem.h>
using namespace NEPHILIM_NS;

class CommandCreateProjectDataSheet : public NativeCommand
{
public:
	void execute(String command);
};

#endif // CommandCreateProject_h__
