#ifndef Info_h__
#define Info_h__

#include "Command.h"

#include <Nephilim/File.h>
#include <Nephilim/Strings.h>
using namespace NEPHILIM_NS;

#include <vector>
#include <map>

class ProjectConfig
{
public:
	ProjectConfig();

	bool load(const String& filename);

	bool saveDefault(const String& filename);

	std::map<String, String> m_entries;
};

class Info
{
public:
	static void init();

	static String assetPath;

	static NativeCommand* getCommand(const String& name);

	static std::map<String, NativeCommand*> nativeActions;

};

void replaceTokensInFile(const String& filename, std::map<String,String> dictionary);
String replaceTokensInString(String str, std::map<String,String> dictionary);
#endif // Info_h__
