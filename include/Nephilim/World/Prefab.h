#ifndef NephilimSceneFormat_h__
#define NephilimSceneFormat_h__

#include <Nephilim/Foundation/Asset.h>
#include <Nephilim/Foundation/String.h>

#include <vector>
#include <map>

NEPHILIM_NS_BEGIN

/**
	\class Prefab
	\brief Defines the structure of prefab objects for instantiation

	Usually, all object types are loaded in memory, and are used to quickly
	spawn and setup instances of the prefab.
*/
class NEPHILIM_API Prefab : public Asset
{
public:
	struct Spawn
	{
		String prefab;
	};

	struct ComponentInfo
	{
		String tag;
		std::map<String, String> attributes;

		void set(const String& key, const String& val)
		{
			attributes[key] = val;
		}

		String get(const String& key) const
		{
			return attributes.find(key)->second;
		}
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

	/// This specifies the prefab root (what it spawns)
	String rootClassName;

	/// We have N components in our prefab, which we instance by name
	struct ComponentInstance
	{
		String ComponentClass;

		std::vector<ComponentInstance*> SubComponents;
	};

	std::vector<ComponentInstance> ComponentInstances;


	struct GameObjectPrefab
	{
		std::vector<ComponentInstance*> Components;
		String Class;
	};

	std::vector<GameObjectPrefab> GameObjectPrefabs;

public:

	/// Returns true if the prefab instances more than one game object
	bool isMultiGameObject();

	String getRootClassName() const
	{
		return rootClassName;
	}

	bool loadjson(const String& filename);

	bool load(const String& filename);
	bool save(const String& filename);
};

/*TEntity SpawnPrefab(Prefab prefab, World w)
{

}*/

NEPHILIM_NS_END
#endif // NephilimSceneFormat_h__
