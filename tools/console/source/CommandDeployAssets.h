#ifndef CommandDeployAssets_h__
#define CommandDeployAssets_h__

#include <Nephilim/FileSystem.h>
#include <Nephilim/File.h>
using namespace NEPHILIM_NS;

#include "Command.h"

void deployHandleDirectory(String directory, String dest);

class CommandDeployAssets : public NativeCommand
{
	void execute(String command)
	{
		bool isProjectDirectory = false;
		{
			File fp("project.data", IODevice::BinaryRead);
			isProjectDirectory = fp.isReady();
		}

		if(isProjectDirectory)
		{
			cout << "[Console] Valid project directory. Reassembling assets." << endl;
			deployHandleDirectory("assets", "apk/assets");
		}
	}
};

void deployHandleDirectory(String directory, String dest)
{
	FileSystem::makeDirectory(dest); 

	StringList flist = FileSystem::scanDirectory(directory, "*", false);
	for(unsigned int i = 0; i < flist.size(); i++){
		String relativepath = flist[i];
		if(flist[i].find_last_of('/') != flist[i].npos)
			flist[i].erase(flist[i].begin(), flist[i].begin() + flist[i].find_last_of('/')+1);

		cout<<"[Console] Installing file: "<<flist[i]<<endl;


		if(!FileSystem::isDirectory(relativepath)){

			if(!	fs::copyFile(directory + "/" + flist[i], dest + "/" + flist[i] + ".png") ) 
				cout<<"Failed to install file."<<endl;
		}
	}
	

	/// Check nested directories within this one
	StringList list = FileSystem::directoryList(directory, false);
	for(unsigned int i = 0; i < list.size(); i++){
		cout<<"[Console] Deploying directory: "<<directory + "/" + list[i]<<endl;
		deployHandleDirectory(directory + "/" + list[i], dest + "/" + list[i]);
	}
}

#endif // CommandDeployAssets_h__
