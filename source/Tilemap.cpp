#include <Nephilim/Tilemap.h>
#include <pugixml/pugixml.hpp>

NEPHILIM_NS_BEGIN

bool Tilemap::loadTMX(const String& filename)
{
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file(filename.c_str());

	if(!result)
	{
		return false;
	}

	pugi::xml_node root_node = doc.first_child();

	for(pugi::xml_node_iterator it = root_node.begin(); it != root_node.end(); ++it)
	{
		if(String(it->name()) == "layer")
		{
			Layer* layerData = new Layer();

			// Fill basic data
			layerData->mWidth = it->attribute("width").as_int();
			layerData->mHeight = it->attribute("height").as_int();
			layerData->mName = it->attribute("name").as_string();
			layerData->mType = 1;

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


//////////////////////////////////////////////////////////////////////////

int Tilemap::Layer::getTileCount()
{
	return mTileData.size();
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