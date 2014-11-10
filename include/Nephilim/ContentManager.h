#ifndef NephilimContentBank_h__
#define NephilimContentBank_h__

#include <Nephilim/Platform.h>
#include <Nephilim/VirtualFS.h>
#include "StringID.h"
#include "ContentList.h"
#include "ContentLoader.h"
#include <Nephilim/Graphics/GLTexture.h>
#include "Font.h"
#include "File.h"
#include <Nephilim/Model/Mesh.h>
#include <Nephilim/Plugins/Plugin.h>

#include <map>
#include <memory>

NEPHILIM_NS_BEGIN

class ContentGroupFonts
{
public:
	bool load(const String& filename);

	std::map<String, Font*> mFonts;
};

class MeshResource
{
public:

	/// The list of meshes in this resource
	std::vector<Mesh> meshes;
};

/// A content group holds an indefinite number of resources of different types
class ContentGroup
{
public:

	ContentGroupFonts mFonts;

	std::map<String, Texture*> mTextures;
	std::map<String, MeshResource*> mMeshes;
};


/// Content manager manages all content groups created
class ContentManager
{
public:
	/// Creates the default group - no name ""
	ContentManager();

	/// Ensure removal of all content groups and the resources
	~ContentManager();

	ContentGroup* createGroup(const String& name);

	/// Order the content manager to create a new mesh with a given resource id
	MeshResource* createMesh(const String& resource_id);

	void removeGroup(const String& name);

	/// The most elemental form of loading an asset
	/// Simply takes the filename and tries to deduce how to load it from extension
	bool load(const String& filename);

	Texture* getTexture(const String& name);

	String mDefaultGroup; ///< The current default group
	ContentGroupFonts* mDefaultFonts; ///< A pointer to the font holder in the currently "default" group

	std::map<String, ContentGroup*> mGroups;

	VirtualFS* filesystems;

	std::vector<std::unique_ptr<Plugin> > plugins;
};















namespace Content
{
	enum KnownResourceTypes
	{
		Texture = 0,
		Font,
		SoundBuffer,
		Count
	};
};

class GameCore;
/**
	\ingroup Content
	\class ContentBank
	\brief Represents a warehouse for different kinds of resources.

	You may never instance yourself a ContentBank object, as the engine can never lose track
	of all the content loaded by the running games.

	This happens because the engine can assure the destruction of each game's content.

	Another important reason is for the Scripting support. The scripts will reach the resources easier
	and you don't have to tire yourself doing it.

	A ContentBank is meant to have only resources that are currently loaded in memory.
	However, you can see ContentList class as a way to have multiple lists of resources, which can be loaded/unloaded all at once.

	In cases of omission, the engine understands a few file formats and loads them as determined formats.

	Here is the list:

		- png, jpg, tga ... ( loaded as Textures )
		- ps, vs, fx ( loaded as Shaders )
		- ogg, wav ... ( loaded as SoundBuffers )
		- ...

*/
class NEPHILIM_API ContentBank
{
public:
	/// Creates a loose content bank, destroys its resources on destruction
	ContentBank();

	/// Attempts to open a raw file
	File* openRawFile(const String& path, const String& openMode);

	/// Loads a resource by inferring its extension
	bool load(const String& path);

	/// Registers an extension to a resource type - Content::KnownResourceTypes for the built in types
	void registerResourceType(const String& extension, Uint32 type_id);

	/// Loads the entries of the ContentList into memory
	/// All resources will be known as its alias
	/// Resources with aliases already loaded are ignored, and a log warning is issued
	/// Alias of a resource is also what identifies the resource in a search
	void loadContentList(ContentList &list, bool storeList);

	/// Unloads all resources that have entry in the ContentList
	/// When unloading the list, the alias will be used to locate all the resources that belong to the list
	void unloadContentList(ContentList &list);

	/// Create a sound buffer
	void createSoundBuffer(const String &name);

	/// Get a previously loaded sound buffer
//	sf::SoundBuffer* getSoundBuffer(const String &name);

	/// Temp
	/// Creates a texture from a file
	bool loadTexture(const String &fileName);

	/// Get the texture
	Texture* getTexture(const String &texture_name);

	String m_rootPath;

private:
	friend class GameCore;

	/// Private constructor - only friends can instance ContentBank
	ContentBank(GameCore *parent, const String &name);

	/// ContentBank name
	String myName;

	/// If true, when trying to read a resource, it is automatically loaded.
	/// More for prototyping and it doesn't allow to take full advantage of the engine.
	bool myLoadOnRequest;

	//Resource Pools
	std::map<String, Texture*> myTextureResources;
	//std::map<String, sf::SoundBuffer*> mySoundResources;
};

/**
	\class TextureList
	\brief List of named texture objects
*/
class NEPHILIM_API TextureList
{
public:

	class NEPHILIM_API TextureItem
	{
	public:
		Texture* object;
	};

	std::map<String, TextureItem> textures;
};

NEPHILIM_NS_END
#endif // NephilimContentBank_h__
