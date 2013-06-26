#include "CommandCreateProjectDataSheet.h"
#include "Info.h"

void CommandCreateProjectDataSheet::execute(String command)
{
	ProjectConfig config;
	config.saveDefault("project.data");
}