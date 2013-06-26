#include "CommandCreateProject.h"
#include "CommandCreateProjectDataSheet.h"

#include <iostream>
using namespace std;

void CommandCreateProject::execute(String command)
{
	CommandCreateProjectDataSheet* program = static_cast<CommandCreateProjectDataSheet*>(Info::nativeActions["datasheet"]);
	if(program)
	{
		program->execute("");
	}

	FileSystem::makeDirectory("assets");
}