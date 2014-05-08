#include <Nephilim/ContentBank.h>
#include <Nephilim/Path.h>
#include <Nephilim/Clock.h>
#include <Nephilim/Logger.h>

#include <iostream>
using namespace std;

NEPHILIM_NS_BEGIN

ContentManager::ContentManager()
: mDefaultGroup("")
{
	// Create the anonymous group where assets are loaded to by default
	createGroup("");
	mDefaultFonts = &mGroups[""]->mFonts;
}

ContentManager::~ContentManager()
{
	while(!mGroups.empty())
	{
		removeGroup(mGroups.begin()->first);
	}
}


ContentGroup* ContentManager::createGroup(const String& name)
{
	mGroups[name] = new ContentGroup();
	return mGroups[name];
}

void ContentManager::removeGroup(const String& name)
{
	if(mGroups.find(name) != mGroups.end())
	{
		delete mGroups[name];
		mGroups.erase(mGroups.find(name));
	}
}

/// The most elemental form of loading an asset
/// Simply takes the filename and tries to deduce how to load it from extension
bool ContentManager::load(const String& filename)
{
	// Make sure there is a target content holder
	if(mGroups.find(mDefaultGroup) == mGroups.end())
		return false;

	String extension = Path(filename).getExtension();
	extension.toLowerCase();

	ContentGroup* targetGroup = mGroups[mDefaultGroup];

	if(extension == "png")
	{
		Log("Loading texture: %s", filename.c_str());
		targetGroup->mTextures[filename] = new Texture();
		return targetGroup->mTextures[filename]->loadFromFile(filename);
	}
	else if(extension == "ttf" || extension == "otf")
	{
		Log("Loading font: %s", filename.c_str());
		return targetGroup->mFonts.load(filename);
	}

	return false;
}

Texture* ContentManager::getTexture(const String& name)
{
	if(mGroups[mDefaultGroup]->mTextures.find(name) == mGroups[mDefaultGroup]->mTextures.end())
		return NULL;

	return mGroups[mDefaultGroup]->mTextures[name];
}





//////////////////////////////////////////////////////////////////////////
bool ContentGroupFonts::load(const String& filename)
{
	if(mFonts.find(filename) == mFonts.end())
	{
		mFonts[filename] = new Font();
	}

	return mFonts[filename]->loadFromFile(filename);
}
//////////////////////////////////////////////////////////////////////////





/// Creates a loose content bank, destroys its resources on destruction
ContentBank::ContentBank()
: myLoader(this)
{
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

bool ContentBank::loadTexture(const String &fileName)
{
	// -- The requested texture doesn't exist, create it and return it
	if(myTextureResources.find(fileName) == myTextureResources.end())
	{
		myTextureResources[fileName] = new Texture();
	}

	Clock t;

	bool result = myTextureResources[fileName]->loadFromFile(fileName);

	//Log("Loading %s took %d ms", fileName.c_str(), t.getElapsedTime().asMiliSeconds());

	return result;
}

/// Temp
/// Get the texture
Texture* ContentBank::getTexture(const String &texture_name)
{
	// -- The requested texture doesn't exist, create it and return it
	if(myTextureResources.find(texture_name) == myTextureResources.end())
	{
		myTextureResources[texture_name] = new Texture();
	}

	return myTextureResources[texture_name];
};

NEPHILIM_NS_END
