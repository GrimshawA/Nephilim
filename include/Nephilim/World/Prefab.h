#ifndef NephilimSceneFormat_h__
#define NephilimSceneFormat_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Strings.h>

#include <vector>

NEPHILIM_NS_BEGIN

/**
	\class Prefab
	\brief Defines the structure of prefab objects for instantiation
*/
class NEPHILIM_API Prefab
{
public:
	struct Spawn
	{
		String prefab;
	};

	struct ComponentInfo
	{
		String tag;
	};

	struct SubObject
	{
		std::vector<ComponentInfo> components;
	};

	/// List of spawns from other prefabs
	std::vector<Spawn> spawns;

	/// List of things that need to be instanced
	std::vector<ComponentInfo> objectData;

	/// Lists of things that need to be instanced as children
	std::vector<SubObject> subObjectData;

public:
	bool load(const String& filename);
	bool save(const String& filename);
};

/*TEntity SpawnPrefab(Prefab prefab, World w)
{

}*/

NEPHILIM_NS_END
#endif // NephilimSceneFormat_h__
