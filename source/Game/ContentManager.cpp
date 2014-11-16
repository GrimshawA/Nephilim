#include <Nephilim/ContentManager.h>
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

	filesystems = new VirtualFS();
	filesystems->indexSearchPath("./", "/");
}

ContentManager::~ContentManager()
{
	while(!mGroups.empty())
	{
		removeGroup(mGroups.begin()->first);
	}
}

/// Order the content manager to create a new mesh with a given resource id
MeshResource* ContentManager::createMesh(const String& resource_id)
{
	return new MeshResource();
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

	if(extension == "png" || extension == "jpg")
	{
		bool r = false;

		String realPath = filesystems->translate(filename);

		if(filesystems->exists(filename))
		{
			Log("Going to load texture %s at real path: %s", filename.c_str(), realPath.c_str());

			targetGroup->mTextures[filename] = new Texture();
			r = targetGroup->mTextures[filename]->loadFromFile(realPath);
			targetGroup->mTextures[filename]->setSmooth(false);
			targetGroup->mTextures[filename]->setRepeated(false);
		}
		else
		{
			Log("Failed to load image, file not found");
		}
	
		return r;
	}
	else if(extension == "ttf" || extension == "otf")
	{
		//Log("Loading font: %s", filename.c_str());
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

NEPHILIM_NS_END
