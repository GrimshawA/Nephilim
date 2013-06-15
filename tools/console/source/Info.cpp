#include "Info.h"

#include <Nephilim/FileSystem.h>
#include <Nephilim/Logger.h>
using namespace NEPHILIM_NS;

String Info::assetPath = "";
std::map<String, NativeCommand*> Info::nativeActions; 

void Info::init()
{
	assetPath = FileSystem::getExecutableDirectory() + "ncassets/";
	//Log("%s", assetPath.c_str());
}

NativeCommand* Info::getCommand(const String& name)
{
	return nativeActions[name];
}

