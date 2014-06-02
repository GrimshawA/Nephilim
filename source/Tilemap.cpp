#include <Nephilim/Tilemap.h>
#include <Nephilim/Logger.h>

#include <pugixml/pugixml.hpp>


NEPHILIM_NS_BEGIN

namespace
{
	bool hasChild(const String& name, pugi::xml_node& node)
	{
		for(pugi::xml_node_iterator it = node.begin(); it != node.end(); ++it)
		{
			if(String(it->name()) == name)
				return true;
		}

		return false;
	}
};

bool Tilemap::loadTMX(const String& filename)
{
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file(filename.c_str());

	if(!result)
	{
		return false;
	}

	pugi::xml_node root_node = doc.first_child();

	mWidth = root_node.attribute("width").as_int(0);
	mHeight = root_node.attribute("height").as_int(0);
	mTileWidth = root_node.attribute("tilewidth").as_int(0);
	mTileHeight = root_node.attribute("tileheight").as_int(0);

	for(pugi::xml_node_iterator it = root_node.begin(); it != root_node.end(); ++it)
	{
		if(String(it->name()) == "layer")
		{
			Layer* layerData = new Layer();

			// Fill basic data
			layerData->mWidth = it->attribute("width").as_int();
			layerData->mHeight = it->attribute("height").as_int();
			layerData->mName = it->attribute("name").as_string();
			layerData->mType = Layer::Tiles;

			// Allocate data
			layerData->mTileData.resize(layerData->mWidth * layerData->mHeight);

			// <data> is under <layer>. It has N tile children
			pugi::xml_node tile_layer_data = it->child("data");
			int tile_count_check = 0;
			for(pugi::xml_node_iterator tile_iterator = tile_layer_data.begin(); tile_iterator != tile_layer_data.end(); ++tile_iterator)
			{
				layerData->mTileData[tile_count_check] = tile_iterator->attribute("gid").as_int(0);
				tile_count_check ++;
			}

			mLayers.push_back(layerData);
		}
		else if(String(it->name()) == "objectgroup")
		{
			Layer* layerData = new Layer();

			// Fill basic data
			layerData->mWidth = it->attribute("width").as_int();
			layerData->mHeight = it->attribute("height").as_int();
			layerData->mName = it->attribute("name").as_string();
			layerData->mType = Layer::Objects;

			for(pugi::xml_node_iterator object_it = it->begin(); object_it != it->end(); ++object_it)
			{
				Tilemap::Object obj;
				obj.mName = object_it->attribute("name").as_string();
				obj.mType = object_it->attribute("type").as_string();

				pugi::xml_node propertiesNode =  object_it->child("properties");

				for(pugi::xml_node_iterator prop_it = propertiesNode.begin(); prop_it != propertiesNode.end(); ++prop_it)
				{
					if(String(prop_it->name()) == "property")
					{
						obj.mProperties[prop_it->attribute("name").as_string()] = prop_it->attribute("value").as_string();
					}
				}

				// Check the geometry type
				if(hasChild("ellipse", (*object_it)) )
				{
					Log("ELLIPSE");
				}
				else if(hasChild("polygon", (*object_it)))
				{
					Log("POLYGON");

				}
				else if(hasChild("polyline", (*object_it)))
				{
					Log("POLYLINE");

				}
				else // Rectangle
				{
					obj.mObjectType = Object::Rectangle;
					obj.mName = (*object_it).attribute("name").as_string("");

					obj.mPosition.x = (*object_it).attribute("x").as_float(0);
					obj.mPosition.y = (*object_it).attribute("y").as_float(0);
					obj.mPoints.push_back(vec2((*object_it).attribute("width").as_float(1), (*object_it).attribute("height").as_float(1)));
				}
				layerData->mObjects.push_back(obj);
			}

			mLayers.push_back(layerData);
		}
	}

	return true;
}

int Tilemap::getLayerCount()
{
	return static_cast<int>(mLayers.size());
}

Tilemap::Layer* Tilemap::getLayer(int index)
{
	return mLayers[index];
}

Tilemap::Layer* Tilemap::getLayerByName(const String& name)
{
	for(size_t i = 0; i < mLayers.size(); ++i)
	{
		if(mLayers[i]->mName == name)
			return mLayers[i];
	}

	return NULL;
}


//////////////////////////////////////////////////////////////////////////

int Tilemap::Layer::getTileCount()
{
	return mTileData.size();
}

int Tilemap::Layer::getTile(int index)
{
	return mTileData[index];
}

int Tilemap::Layer::getType()
{
	return mType;
}

vec2 Tilemap::Layer::getObjectPosition(const String& name)
{
	for(size_t i = 0 ; i < mObjects.size(); ++i)
	{
		if(mObjects[i].mName == name)
		{
			return mObjects[i].mPosition;
		}
	}

	return vec2(0.f, 0.f);
}


void Tilemap::Layer::getTileShape(int index, float& x, float& y, float& w, float& h)
{
	if(mTileData[index] == 0)
	{
		//no where
	}
	else
	{
		int tile_index = 0;
		for(int j = 0; j < mHeight; ++j)
		{
			for(int i = 0; i < mWidth; ++i)
			{
				if(tile_index == index)
				{
					x = i * 32.f + 16.f;
					y = j * 32.f + 16.f;
					w = 32.f;
					h = 32.f;
				}
				tile_index ++;
			}
		}
	}
}




NEPHILIM_NS_END