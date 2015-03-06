#ifndef NephilimGameContent_h__
#define NephilimGameContent_h__

#include <Nephilim/Platform.h>

#include <Nephilim/Foundation/VirtualFileSystem.h>
#include <Nephilim/Foundation/StringHash.h>
#include <Nephilim/Foundation/File.h>
#include <Nephilim/Foundation/PluginLoader.h>

#include <Nephilim/Game/Resource.h>

#include <Nephilim/Graphics/Font.h>
#include <Nephilim/Graphics/Sprite.h>
#include <Nephilim/Graphics/Texture2D.h>

#include <map>
#include <memory>

NEPHILIM_NS_BEGIN

class StaticMesh;
class SkeletalMesh;
class ExtensionImporter;


// used to assist in automatic loading of third party importers
// not needed for native formats
struct ModelImportSettings
{

};

/// Content manager manages all content groups created
class GameContent
{
public:

	Font font;

	/// List of custom model loaders currently plugged in
	/// This is just for third party formats, all native binary ones are handled automatically
	std::vector<ExtensionImporter*> modelLoaders;

	std::vector<StaticMesh*> staticMeshContainer;
	std::vector<String>      staticMeshNames;

	std::vector<SkeletalMesh*> skeletalMeshContainer;
	std::vector<String>      skeletalMeshNames;

	typedef std::pair<String, Sprite> SpriteResource;
	std::vector<SpriteResource> sprites;

	VirtualFileSystem virtualfs;

	std::vector<std::unique_ptr<PluginLoader> > plugins;

	/// All allocated textures
	std::vector<Texture2D*> _textures;

public:

	/// Creates the default group - no name ""
	GameContent();

	/// Ensure removal of all content groups and the resources
	~GameContent();

	/// Create a new static mesh with a given resource name
	StaticMesh* createStaticMesh(const String& urn);

	/// Create a new static mesh with a given resource name
	SkeletalMesh* createSkeletalMesh(const String& urn);

	Texture2D* createTexture(const String& filename);

	/// This will cause a static mesh to be loaded from a file with native loader or an importer
	bool loadStaticMesh(const String& urn, const String& filename);
	
	/// Find a mesh in our storage, so it can be used somewhere
	Resource<StaticMesh> findMesh(const String& name);

	/// Load a font
	void loadFont(const String& filename);

	/// The most elemental form of loading an asset
	/// Simply takes the filename and tries to deduce how to load it from extension
	bool load(const String& filename);

	Texture2D* getTexture(const String& name);
};

NEPHILIM_NS_END
#endif // NephilimGameContent_h__
