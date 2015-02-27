#include <Nephilim/AngelScriptEXT/ASXRegistrationUI.h>
#include <Nephilim/AngelScriptEXT/ASXEngine.h>
#include <Nephilim/Foundation/Logging.h>
#include <Nephilim/Foundation/File.h>

#include <angelscript.h>

namespace
{
	void dummy()
	{

	}
};

NEPHILIM_NS_BEGIN

/// It would be interesting to implement here a std::map with object to ref count assignment. This would allow for application side Files to be ignored for reference counting,
/// and also the ones allocated from script would be reference counted just fine, while keeping the class clean.
/// Highly likely for future implementation

class ScriptFile : public File
{
public:
	int mReferences;
};

ScriptFile* FileInstancer()
{
	Log("File allocated.");
	ScriptFile* scriptFile = new ScriptFile();
	scriptFile->mReferences = 1;
	return scriptFile;
}

void FileAddRef(ScriptFile* obj)
{
	Log("File ref increased.");
	obj->mReferences ++;
}

void FileReleaseRef(ScriptFile* obj)
{
	obj->mReferences --;
	if(obj->mReferences == 0)
	{
		delete obj;
		Log("File released.");
	}
}

void registerFileASX(ASXEngine& engine)
{
	engine.get()->RegisterObjectType("File", sizeof(ScriptFile), asOBJ_REF);

	engine.get()->RegisterObjectBehaviour("File", asBEHAVE_FACTORY, "File@ f()", asFUNCTION(FileInstancer), asCALL_CDECL);
	engine.get()->RegisterObjectBehaviour("File", asBEHAVE_ADDREF, "void f()", asFUNCTION(FileAddRef), asCALL_CDECL_OBJLAST);
	engine.get()->RegisterObjectBehaviour("File", asBEHAVE_RELEASE, "void f()", asFUNCTION(FileReleaseRef), asCALL_CDECL_OBJLAST);

	engine.get()->RegisterObjectMethod("File", "bool open(const string& in)", asMETHODPR(ScriptFile, open, (const String&), bool), asCALL_THISCALL);
	engine.get()->RegisterObjectMethod("File", "string getLine()", asMETHOD(ScriptFile, getLine), asCALL_THISCALL);
	engine.get()->RegisterObjectMethod("File", "bool atEnd()", asMETHOD(ScriptFile, atEnd), asCALL_THISCALL);

}

NEPHILIM_NS_END