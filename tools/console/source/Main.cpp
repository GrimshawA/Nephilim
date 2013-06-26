#include <Nephilim/Strings.h>
#include <Nephilim/Engine.h>
#include <Nephilim/ASEngine.h>

#include "Info.h"
#include "CommandCreateProject.h"
#include "CommandCreateProjectDataSheet.h"
#include "CommandModelConverter.h"
#include "CommandGenerateAPK.h"
#include "CommandPackager.h"
#include "CommandDeployAssets.h"

#include <iostream>

using namespace NEPHILIM_NS;
using namespace std;

std::map<String, NativeCommand*> nativeActions;

struct scriptAction
{
	String description;
	ASScript* script;
};
//ASEngine					scriptEngine;
std::map<String, scriptAction> scriptActions;

void initScriptActions()
{
	/*scriptEngine.exportStrings();

	StringList list = FileSystem::scanDirectory(Info::assetPath + "NephilimConsoleResources/actions", "*", false);
	for(unsigned int i = 0; i < list.size(); i++)
	{
		String actionName = list[i];
		actionName.erase(actionName.begin(), actionName.begin() + actionName.find_last_of('/') + 1);
		actionName.erase(actionName.begin() + actionName.find_last_of('.'), actionName.end());
		scriptActions[actionName].script = scriptEngine.loadScript(list[i]);
		if(scriptActions[actionName].script)
		{
			scriptActions[actionName].description = scriptActions[actionName].script->fastCall<String>("string description()");
		}
	}*/
}

void runScriptAction(const String& actionName)
{
	/*ASScript* script = scriptActions[actionName].script;
	if(script)
	{
		script->call(String("void run()"));
	}*/
}

void printcharn(char c, int n)
{
	for(int i = 0; i < n; i ++){
		cout<<c;
	}
}

void showHelp(){
	cout<<endl;
	cout<<"NephilimConsole v"<<Engine::getVersionString()<<endl;
	cout<<"Copyright (C) 2010-2013 Artur Moreira and the Nephilim project"<<endl
		<< endl;
	cout<<"Usage: action [parameters]"<<endl
		<< endl;
	cout<<"ACTIONS"<<endl
		<<endl;
	cout<<" "<<"gen-apk"<<endl;
	cout<<endl;

	/*for(std::map<String, scriptAction>::iterator it = scriptActions.begin(); it != scriptActions.end(); ++it)
	{
		cout << " " << it->first;
		printcharn(' ', 30 - it->first.length() + 1);
		cout <<  it->second.description << endl;
	}*/
}

void runNativeAction(String command)
{
	nativeActions[command.split(' ').front()]->execute(command);
}

bool isScriptAction(String command)
{
	return false;
}

bool isNativeAction(String command)
{
	return nativeActions.find(command) != nativeActions.end();
}

void processCommand(String command)
{
	if(command == "help")
	{
		showHelp();
	}
	else if(isScriptAction(command.split(' ').front()))
	{
		runScriptAction(command);
	}
	else if(isNativeAction(command.split(' ').front()))
	{
		runNativeAction(command);
	}
	else
	{
		cout << "Sorry, I don't know what you mean." << endl;
	}
}

int main(int argc, char** argv)
{
	Info::assetPath = FileSystem::getExecutableDirectory() + "ncassets/";

	// Init native commands
	nativeActions["init"]  = new CommandCreateProject();
	nativeActions["datasheet"]  = new CommandCreateProjectDataSheet();
	nativeActions["mesh"] = new CommandModelConverter();
	nativeActions["pack"] = new CommandPackager();
	nativeActions["sync-assets"] = new CommandDeployAssets();
	nativeActions["apk"] = new CommandGenerateAPK();

	Info::nativeActions = nativeActions;
	
	// Init script commands
	initScriptActions();

	// Interactive mode
	if(argc == 1)
	{
		cout << "Welcome to the interactive mode. Type 'q' to exit." << endl;
		String command;
		while(command != "q")
		{
			cout << "> "; getline(cin, command);

			if(command != "q")
			{
				processCommand(command);
			}
			else
			{
				cout << "Bye!" << endl;
			}
		}
	}
	// Single command
	else
	{
		String cmd;
		for(int i = 1; i < argc; ++i)
		{
			cmd += String(argv[i]);
			if(i+1 < argc) cmd += " ";
		}
		processCommand(cmd);
	}
	
	return 0;
}