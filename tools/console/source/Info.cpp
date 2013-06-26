#include "Info.h"

#include <iostream>

#include <Nephilim/FileSystem.h>
#include <Nephilim/Logger.h>
#include <Nephilim/TextStream.h>
using namespace NEPHILIM_NS;
using namespace std;

String Info::assetPath = "";
std::map<String, NativeCommand*> Info::nativeActions; 

String trimString(String s)
{
	while(s.find_first_of('\n') != s.npos)
	{
		s.erase(s.begin() + s.find_first_of('\n'));
	}

	while(!s.empty() && s[0] == ' ') s.erase(s.begin());
	while(!s.empty() && s[s.size()-1] == ' ') s.erase(s.begin() + s.size() - 1);
	return s;
}

ProjectConfig::ProjectConfig()
{
	m_entries["ANDROID_PACKAGE"]                       = "com.nephilim.game";
	m_entries["ANDROID_ACTIVITY"]                      = "GameActivity";
	m_entries["ANDROID_AIRPUSH_IMPORT"]                = "";
	m_entries["ANDROID_LINK_LIBRARY"]                  = "ProjectNameHere";
	m_entries["ANDROID_AIRPUSH_INIT"]                  = "";
	m_entries["ANDROID_TARGET_API"]                    = "android-10";
	m_entries["ANDROID_APP_VERSION"]                   = "1.0";
	m_entries["ANDROID_MANIFEST_AIRPUSH"]              = "";
	m_entries["ANDROID_MANIFEST_ACTIVITY_ORIENTATION"] = "landscape";
	m_entries["ANDROID_MANIFEST_ICON_DEFINITION"]      = "android:icon=\"@drawable/icon_launcher\"";
	m_entries["ANDROID_MANIFEST_MINSDK"]               = "4"; 
	m_entries["ANDROID_APP_LABEL"]                     = m_entries["ANDROID_ACTIVITY"]; 
	m_entries["ANDROID_ACTIVITY_LABEL"]                = m_entries["ANDROID_ACTIVITY"]; 


	//m_entries["ANDROID_AIRPUSH_INIT"] = "/// Airpush initialization
		//new Airpush(getApplicationContext(), "52201","1337301308105398636",true,true,true);";	

}


bool ProjectConfig::load(const String& filename)
{
	File fp(filename, IODevice::TextRead);
	if(fp)
	{
		while(!fp.atEnd())
		{			
			String line = fp.getLine();

			if(line[0] == '[' || line[0] == '\n' ||  line[0] == '\r' || line[0] == '-' || line.empty())
			{

			}
			else
			{
				StringList option = line.split('=', 1);

				if(option.size() == 2)
				{
					m_entries[trimString(option[0])] = trimString(option[1]);

				//	cout << "Option: " << trimString(option[0]) <<"|"<< endl;
					//cout << "Param: " << trimString(option[1]) <<"|"<< endl;
				}
			}
		}
	}

	return true;
}

bool ProjectConfig::saveDefault(const String& filename)
{
	File dstFile(filename, IODevice::TextWrite);
	if(dstFile)
	{
		TextStream dstStream(dstFile);

		dstStream << "[GENERAL]\n";
		dstStream << "PROJECT_NAME = STUFF\n";
		dstStream << "\n";
		dstStream << "[ANDROID]\n";
		dstStream << "ANDROID_PACKAGE = " << m_entries["ANDROID_PACKAGE"] << "\n";
		dstStream << "ANDROID_ACTIVITY = " << m_entries["ANDROID_ACTIVITY"] << "\n";
		dstStream << "ANDROID_LINK_LIBRARY = " << m_entries["ANDROID_LINK_LIBRARY"] << "\n";
		dstStream << "";

		return true;
	}
	else
		return false;
}



void Info::init()
{
	assetPath = FileSystem::getExecutableDirectory() + "ncassets/";
	//Log("%s", assetPath.c_str());
}

NativeCommand* Info::getCommand(const String& name)
{
	return nativeActions[name];
}


String replaceTokensInString(String str, std::map<String,String> dictionary)
{
	bool inToken = false;
	int pos = -1;
	String cache;
	for(unsigned int i = 0; i < str.length(); i++){		
		if(str[i] == '%')
		{
			if(inToken)
			{
				if(dictionary.find(cache) != dictionary.end())
				{
					str.replace(str.begin() + pos, str.begin() + i + 1, dictionary[cache].begin(), dictionary[cache].end());
					i =  (unsigned int)( pos + dictionary[cache].length());
				}

				cache.clear();
				inToken = false;
			}
			else{
				pos = i;
				inToken = true;
			}
		}
		else if(inToken)
		{
			//record the token
			cache += str[i];
		}
	}

	return str;
}

void replaceTokensInFile(const String& filename, std::map<String,String> dictionary)
{
	fs::copyFile(filename, "tmpfile");

	File txtFile("tmpfile", IODevice::TextRead);
	File dstFile(filename,  IODevice::TextWrite);
	if(txtFile && dstFile)
	{
		while(!txtFile.atEnd())
		{
			String line = txtFile.getLine();
			line = replaceTokensInString(line, dictionary);
			TextStream dstStream(dstFile);
			dstStream << line;
		}
	}
	if(::remove("tmpfile") != 0) 
		cout << "Could not remove the temporary files. Do you have permissions?" << endl;
}


