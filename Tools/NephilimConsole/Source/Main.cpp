#include <Nephilim/Strings.h>
#include <iostream>
using namespace pE;
using namespace std;

#ifdef DEBUG
#error Please compile this tool in the release mode.
#endif

#include "APKGenerator.h"
#include "APKAssets.h"

void showHelp(){
	cout<<":Parabola Engine SDK Streamline tool:"<<endl<<endl;
	cout<<":Incorrect arguments, usage should be in the following syntax:"<<endl;
	cout<<"> [gen-apk] <package-name>"<<endl;

	cout<<endl;
}

int main(int argc, char** argv){

	m_ProgramDir = FileSystem::getExecutableDirectory();
	//cout<<m_ProgramDir<<endl;
//	system("pause");

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

	}

	//system("pause");

	return 0;
}