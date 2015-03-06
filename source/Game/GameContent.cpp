#include <Nephilim/Game/GameContent.h>

#include <Nephilim/Graphics/StaticMesh.h>
#include <Nephilim/Graphics/SkeletalMesh.h>

#include <Nephilim/Extensions/ExtensionImporter.h>

#include <Nephilim/Foundation/Path.h>
#include <Nephilim/Foundation/Clock.h>
#include <Nephilim/Foundation/Logging.h>

#include <iostream>
using namespace std;

NEPHILIM_NS_BEGIN

GameContent::GameContent()
{
	virtualfs.indexSearchPath("./", "/");
}

GameContent::~GameContent()
{

}

/// Load a font
void GameContent::loadFont(const String& filename)
{
	font.loadFromFile(filename);
}

/// Create a new static mesh with a given resource name
StaticMesh* GameContent::createStaticMesh(const String& urn)
{
	StaticMesh* m = new StaticMesh;

	staticMeshContainer.push_back(m);
	staticMeshNames.push_back(urn);

	return m;
}

/// Create a new static mesh with a given resource name
SkeletalMesh* GameContent::createSkeletalMesh(const String& urn)
{
	SkeletalMesh* m = new SkeletalMesh;

	skeletalMeshContainer.push_back(m);
	skeletalMeshNames.push_back(urn);

	return m;
}

/// This will cause a static mesh to be loaded from a file with native loader or an importer
bool GameContent::loadStaticMesh(const String& urn, const String& filename)
{
	StaticMesh* m = findMesh(urn).ptr;

	Path path(filename);
	String extension = path.getExtension();

	if (extension == "psk")
	{

	}
	else
	{
		for (std::size_t i = 0; i < modelLoaders.size(); ++i)
		{
			if (modelLoaders[i]->supportsFormat(extension))
			{
				// We found the right loader for this format, let's load
				ModelLoaderParams params;
				params.mesh = m;
				params.filename = filename;
				ModelLoaderResult r = modelLoaders[i]->load(params);

				return true;
			}
		}

		Log("Sorry. Could not load the format: %s", extension.c_str());
	}

	return true;
}

/// Find a mesh in our storage, so it can be used somewhere
Resource<StaticMesh> GameContent::findMesh(const String& name)
{
	//auto i = std::find(staticMeshContainer.begin(), staticMeshContainer.end(), name);

	for (std::size_t i = 0; i < staticMeshContainer.size(); ++i)
	{
		if (staticMeshNames[i] == name)
		{
			return Resource<StaticMesh>(staticMeshContainer[i]);
		}
	}

	return MakeNullResource<StaticMesh>();
}

/// The most elemental form of loading an asset
/// Simply takes the filename and tries to deduce how to load it from extension
bool GameContent::load(const String& filename)
{

	String extension = Path(filename).getExtension();
	extension.toLowerCase();

	if(extension == "png" || extension == "jpg")
	{
		bool r = false;

		String realPath = virtualfs.translate(filename);

		if(1/*filesystems->exists(filename)*/)
		{
			Log("Going to load texture %s at real path: %s", filename.c_str(), realPath.c_str());

		/*	targetGroup->mTextures[filename] = new Texture();
			r = targetGroup->mTextures[filename]->loadFromFile(filename);
			targetGroup->mTextures[filename]->setSmooth(false);
			targetGroup->mTextures[filename]->setRepeated(false);*/
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
		//return targetGroup->mFonts.load(filename);
	}

	return false;
}

Texture2D* GameContent::getTexture(const String& name)
{
	return nullptr;
}

Texture2D* GameContent::createTexture(const String& filename)
{
	Texture2D* NewTexture = new Texture2D;
	NewTexture->loadFromFile(filename);

	_textures.push_back(NewTexture);

	return NewTexture;
}

NEPHILIM_NS_END
