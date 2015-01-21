#ifndef NephilimWorldSerializer_h__
#define NephilimWorldSerializer_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Foundation/String.h>

NEPHILIM_NS_BEGIN

class World;

/**
	\class WorldSerializer
	\brief Loads and saves World objects to files

	This class implements its own approach to World files,
	other serializers could be written if needed.

	Features:
	1) Embedding resources into worlds for a single standalone binary file for the entire world.
	2) World entities referencing external resources (relative to world file, or absolute resource names)
*/
class NEPHILIM_API WorldSerializer
{
public:

	enum FileFormat
	{
		Binary,
		XML,
		JSON,
		NativeText
	};
	
	struct Config
	{
		String filename;
		String extension;

		World* world;

		int format;
		int version;

		bool saveActors;
		bool saveTemporaryActors;
		bool savePrefabAssociations;

		bool resourcesRelativeToWorld;

		bool embedBlueprintResources;
		bool embedSprites;
	};

public:
	/// Initialize the serializer
	WorldSerializer();

	/// Save the world file from the configurable parameters
	bool save_file(const Config& config);

	/// Load the world file from the configurable parameters
	bool load_file(const Config& config);

};

NEPHILIM_NS_END
#endif // NephilimWorldSerializer_h__
