#include <Nephilim/World/WorldSerializer.h>

#include <pugixml/pugixml.hpp>

NEPHILIM_NS_BEGIN

/// Initialize the serializer
WorldSerializer::WorldSerializer()
{

}

/// Save the world file from the configurable parameters
bool WorldSerializer::save_file(const WorldSerializer::Config& config)
{
	bool result = false;

	if (config.format == XML)
	{
		pugi::xml_document document;
		pugi::xml_node rootNode = document.append_child("root");
		
		rootNode.append_child("entity");
		rootNode.append_child("entity");
		rootNode.append_child("entity");

		bool result = document.save_file(config.filename.c_str());
	}

	return result;
}

/// Load the world file from the configurable parameters
bool WorldSerializer::load_file(const WorldSerializer::Config& config)
{
	return true;
}

NEPHILIM_NS_END