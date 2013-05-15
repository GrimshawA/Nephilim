#include <Nephilim/Strings.h>
#include <Nephilim/Engine.h>
#include <Nephilim/ASEngine.h>
#include <iostream>
using namespace pE;
using namespace std;

#ifdef DEBUG
#error Please compile this tool in the release mode.
#endif

#include "APKGenerator.h"
#include "APKAssets.h"

struct scriptAction
{
	String description;
	ASScript* script;
};
ASEngine					scriptEngine;
std::map<String, scriptAction> scriptActions;

void initScriptActions()
{
	scriptEngine.exportStrings();

	StringList list = FileSystem::scanDirectory(m_ProgramDir + "NephilimConsoleResources/actions", "*", false);
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
	}
}

void runScriptAction(const String& actionName)
{
	ASScript* script = scriptActions[actionName].script;
	if(script)
	{
		script->call(String("void run()"));
	}
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

	for(std::map<String, scriptAction>::iterator it = scriptActions.begin(); it != scriptActions.end(); ++it)
	{
		cout << " " << it->first;
		printcharn(' ', 30 - it->first.length() + 1);
		cout <<  it->second.description << endl;
	}
}

int main(int argc, char** argv){

	m_ProgramDir = FileSystem::getExecutableDirectory();
	//cout<<m_ProgramDir<<endl;
//	system("pause");

	initScriptActions();

	

	if(argc < 2){
		//there are no parameters
		showHelp();
		//system("pause");
	}
	else{
		// lets evaluate commands
		String arg1 = argv[1];

		if(arg1 == "gen-apk"){
			//a apk generate

			if(argc < 3){
				cout<<"[Streamline] Too few arguments to generate the APK"<<endl;
			}
			else{
				prepareApkTokens();


				String iconPath;
				String outputDir = "AndroidAPK"; // By default writes to APK directory
				for(int k = 2; k < argc; k++){
					String subcmd = argv[k];

					//is it something useful ?

					if(subcmd.startsWith("-o")){
						//output directory
						outputDir = subcmd;
						outputDir.erase(outputDir.begin(), outputDir.begin() + 2);
						
					}
					else if(subcmd.startsWith("-t")){
						subcmd.erase(subcmd.begin(), subcmd.begin() + 2);
						String token = subcmd;
						StringList splited = token.split('=', 0);
						if(splited.size() == 2){
							TokenContent[splited[0]] = splited[1]; 
						}
						
					}
					else if(subcmd.startsWith("-i")){
						subcmd.erase(subcmd.begin(), subcmd.begin() + 2);
						//request this icon to be added
						iconPath = subcmd;
					}

				}
				cout<<"[Streamline] Starting creation of Android APK"<<endl;
				cout<<"[Streamline] Saving output in: "<<outputDir<<endl;
				if(generateAPK(outputDir, argv[2], 10, iconPath)){
					cout<<"[Streamline] Created an android APK - "<<argv[2]<<endl;
				}
				else{
					cout<<"[Streamline] Failed to create the android APK. Perhaps you are lacking permissions to write files?"<<endl;
				}
			}			
		} // end of gen-apk module
		else if(arg1 == "apk-assets"){
			if(argc < 4){
				cout<<"[Streamline] Too few arguments for asset assembling."<<endl;
			}
			else{
				
				deployAPKAssets(argv[2], argv[3]);
				cout<<"[Streamline] Finished deploying all assets to the target APK."<<endl;
			}
		}
		else
		{
			runScriptAction(arg1);

		}

	}

	//system("pause");

	return 0;
}