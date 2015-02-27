#include <Nephilim/World/Prefab.h>
#include <Nephilim/Foundation/Logging.h>
#include <Nephilim/Foundation/File.h>

#include <pugixml/pugixml.hpp>
#include <json/json.h>
#include <iostream>

NEPHILIM_NS_BEGIN

void JSON_ParseSubObjects(Json::Value& value, Prefab* prefab, Prefab::GameObjectPrefab* ParentGameObject, Prefab::ComponentInstance* ParentComponent)
{
	// value is likely to have components as members
	Json::Value::Members members = value.getMemberNames();
	for (std::size_t i = 0; i < members.size(); ++i)
	{
		Json::Value MemberValue = value[members[i]];

		if (MemberValue.isObject())
		{
			/// This is a sub component
			Prefab::ComponentInstance* CompInstance = new Prefab::ComponentInstance;
			CompInstance->ComponentClass = members[i];

			ParentGameObject->Components.push_back(CompInstance);
			if (ParentComponent)
				ParentComponent->SubComponents.push_back(CompInstance);

			JSON_ParseSubObjects(MemberValue, prefab, ParentGameObject, CompInstance);

			Log("Member name: %s", members[i].c_str());
		}
		else
		{
			// This is a component attribute

		}
	}
}

/// Returns true if the prefab instances more than one game object
bool Prefab::isMultiGameObject()
{
	return GameObjectPrefabs.size() > 1;
}

bool Prefab::loadjson(const String& filename)
{
	Json::Reader reader;
	Json::Value root;

	String doc_string = getTextFileContents(filename);

	bool result = reader.parse(doc_string, root, true);
	if (result)
	{
		Json::Value::Members rootMembers = root.getMemberNames();

		// Each root member is a top level GameObject to spawn
		for (std::size_t i = 0; i < rootMembers.size(); ++i)
		{
			std::cout << rootMembers[i] << std::endl;

			GameObjectPrefab goPrefab;
			goPrefab.Class = rootMembers[i];

			Json::Value GO = root[rootMembers[i]];
			JSON_ParseSubObjects(GO, this, &goPrefab, nullptr);

			GameObjectPrefabs.push_back(goPrefab);
		}



		return true;
	}
	else
		return false;
}







bool Prefab::load(const String& filename)
{
	pugi::xml_document document;
	pugi::xml_parse_result result = document.load_file(filename.c_str());

	if (result)
	{
		pugi::xml_node root_node = document.first_child();
		if (root_node)
		{
			rootClassName = root_node.name();

			auto sprite_components = root_node.children("Sprite");
			for (auto it = sprite_components.begin(); it != sprite_components.end(); ++it)
			{
				ComponentInfo component;
				component.tag = "Sprite";
				component.set("width", it->attribute("width").as_string("100"));
				component.set("height", it->attribute("height").as_string("100"));
				component.set("asset", it->attribute("asset").as_string("!"));
				objectData.push_back(component);
			}

			// Got the root node, probably a valid prefab file, let's parse
			auto spawn_nodes = root_node.children("spawn");
			int count = 0;
			for (auto it = spawn_nodes.begin(); it != spawn_nodes.end(); ++it)
			{
				count++;
				Spawn spawn;
				spawn.prefab = it->attribute("prefab").as_string();
				spawns.push_back(spawn);
			}

			Log("Found %d spawn nodes!", count);
		}

		return true;
	}
	else
	{
		return false;
	}
}

bool Prefab::save(const String& filename)
{
	// Doesn't need implementation yet
	return false;
}
NEPHILIM_NS_END