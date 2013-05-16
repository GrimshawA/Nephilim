#ifndef CommandCreateProject_h__
#define CommandCreateProject_h__

#include "Command.h"
#include "Utility.h"

#include <iostream>
using namespace std;

#include <Nephilim/FileSystem.h>
#include <Nephilim/FileInterface.h>
using namespace NEPHILIM_NS;

class CommandCreateProject : public Command
{
	void run(int argc, char** argv, ProgramContext& context)
	{
		cout<<"Creating Project: "<<argv[2]<<endl;

		// Directory structure
		FileSystem::makeDirectory(argv[2]);
		FileSystem::makeDirectory(String(argv[2]) + "/AndroidAPK");
		FileSystem::makeDirectory(String(argv[2]) + "/Bin");
		FileSystem::makeDirectory(String(argv[2]) + "/Source");
		FileSystem::makeDirectory(String(argv[2]) + "/Build");
		FileSystem::makeDirectory(String(argv[2]) + "/Build/MSVC10");
		cout<<"=> Directory structure done."<<endl;

		// Copy files
		FileInterface::copy(context.resourceDir + "ProjectTemplate/create.bat", String(argv[2]) + "/Android_PrepareAPK.bat");
		FileInterface::copy(context.resourceDir + "ProjectTemplate/CMakeLists.txt", String(argv[2]) + "/CMakeLists.txt");
		FileInterface::copy(context.resourceDir + "ProjectTemplate/test_page.html", String(argv[2]) + "/test_page.html");
		FileInterface::copy(context.resourceDir + "ProjectTemplate/Source/Main.cpp", String(argv[2]) + "/Source/Main.cpp");
		FileInterface::copy(context.resourceDir + "ProjectTemplate/Source/GameTemplate.h", String(argv[2]) + "/Source/" + String(argv[2]) + ".h" );
		cout<<"=> Files copied"<<endl;

		// Arrange files
		fileReplaceToken(String(argv[2]) + "/CMakeLists.txt", "PSPROJECTTEMPLATE", String(argv[2]));
		cout<<"=> Template specialization done."<<endl;

	}
};

#endif // CommandCreateProject_h__
