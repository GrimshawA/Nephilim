#ifndef Command_h__
#define Command_h__

#include "ProgramContext.h"

class Command
{
public:
	virtual void run(int argc, char** argv, ProgramContext& context) = 0;
};

#endif // Command_h__
