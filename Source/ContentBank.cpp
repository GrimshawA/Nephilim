#include "Nephilim/ContentBank.h"
#include "Nephilim/ASEngine.h"
#include "Nephilim/Directory.h"
#include "AS/aswrappedcall.h"

#include <iostream>
using namespace std;

NEPHILIM_NS_BEGIN

bool registerContentBank(ASEngine* engine)
{
	engine->exportReferenceDataType("ContentBank");

	if(engine->getPortableMode())
	{
		engine->getASEngine()->RegisterObjectMethod("ContentBank", "bool loadTexture(const string& in)", WRAP_MFN(ContentBank, loadTexture), asCALL_GENERIC);
		engine->getASEngine()->RegisterObjectMethod("ContentBank", "bool load(const string& in)", WRAP_MFN(ContentBank, load), asCALL_GENERIC);
		engine->getASEngine()->RegisterObjectMethod("ContentBank", "Texture@ getTexture(const string& in)", WRAP_MFN(ContentBank, getTexture), asCALL_GENERIC);
		engine->getASEngine()->RegisterObjectMethod("ContentBank", "File@ openRawFile(const string& in, const string& in)", WRAP_MFN(ContentBank, openRawFile), asCALL_GENERIC);

	}
	else
	{
		engine->getASEngine()->RegisterObjectMethod("ContentBank", "bool loadTexture(const string& in)", asMETHOD(ContentBank, loadTexture), asCALL_THISCALL);
		engine->getASEngine()->RegisterObjectMethod("ContentBank", "bool load(const string& in)", asMETHOD(ContentBank, load), asCALL_THISCALL);
		engine->getASEngine()->RegisterObjectMethod("ContentBank", "Texture@ getTexture(const string& in)", asMETHOD(ContentBank, getTexture), asCALL_THISCALL);
		engine->getASEngine()->RegisterObjectMethod("ContentBank", "File@ openRawFile(const string& in, const string& in)", asMETHOD(ContentBank, openRawFile), asCALL_THISCALL);

	}

	return true;
};


/// Creates a loose content bank, destroys its resources on destruction
ContentBank::ContentBank() : myLoader(this){

	// register most basic ones
	registerResourceType("png", Content::Texture);
	registerResourceType("ttf", Content::Font);
	/// .. and so on
};

/// Attempts to open a raw file // BAD DESIGN
File* ContentBank::openRawFile(const String& path, const String& openMode)
{
	File* file = new File(m_rootPath + path, IODevice::TextRead);
	return file;
};

/// Loads a resource by inferring its extension
bool ContentBank::load(const String& path)
{
	cout<<"[ContentBank] Attempting to identify resource"<<endl;
	Path p;
	p.m_path = path;
	cout<<"[ContentBank] Extension: "<<p.getExtension()<<endl;
	if(p.isRelativePath())
	{
		cout<<"[ContentBank] Is a relative path"<<endl;
	}
	return true;
};

/// Registers an extension to a resource type - Content::KnownResourceTypes for the built in types
void ContentBank::registerResourceType(const String& extension, Uint32 type_id)
{

};

/// Private constructor - only friends can instance ContentBank
ContentBank::ContentBank(GameCore *parent, const String &name) : myLoader(this){
	myName = name;
	myLoadOnRequest = false;
};

/// Loads the entries of the ContentList into memory
/// All resources will be known as its alias
/// Resources with aliases already loaded are ignored, and a log warning is issued
/// Alias of a resource is also what identifies the resource in a search
void ContentBank::loadContentList(ContentList &list, bool storeList){

};

/// Unloads all resources that have entry in the ContentList
/// When unloading the list, the alias will be used to locate all the resources that belong to the list
void ContentBank::unloadContentList(ContentList &list){

};

/// Create a sound buffer
/*void ContentBank::createSoundBuffer(const String &name){
	sf::SoundBuffer *ss = new sf::SoundBuffer();
	ss->loadFromFile(name);
	mySoundResources[name] = ss;
};*/

/// Get a sound buffer
/*sf::SoundBuffer* ContentBank::getSoundBuffer(const String &name){
	return mySoundResources.find(name)->second;
};*/

/// Temp
/// Creates a texture from a file
bool ContentBank::loadTexture(const String &fileName){
	cout<<"[ContentBank] Loading texture: "<<fileName<<endl;
	myTextureResources[fileName] = new Texture();
	return myTextureResources[fileName]->loadFromFile(fileName);
	return false;
};

/// Temp
/// Get the texture
Texture* ContentBank::getTexture(const String &texture_name){
	return myTextureResources[texture_name];
};

NEPHILIM_NS_END