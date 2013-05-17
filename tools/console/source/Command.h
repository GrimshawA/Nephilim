#ifndef Command_h__
#define Command_h__

#include "ProgramContext.h"

class NativeCommand
{
public:
	virtual void run(int argc, char** argv, ProgramContext& context) {};
	
	virtual void execute(String command){}
};

#endif // Command_h__
