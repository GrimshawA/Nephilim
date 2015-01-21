#include <Nephilim/Tilemap.h>
#include <Nephilim/Foundation/File.h>
#include <Nephilim/Foundation/DataStream.h>
#include <Nephilim/Logger.h>
#include <Nephilim/StringList.h>

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

/// This will save the
bool Tilemap::saveToFile(const String& filename, FileFormat format)
{
	if (format == Binary)
	{
		File file(filename, IODevice::BinaryWrite);
		if (file)
		{
			DataStream stream(file);
			stream << width;
			stream << height;
			stream << uint32_t(slices.size());

			for (MapSlice& s : slices)
			{
				file.write(reinterpret_cast<char*>(&s.tileData[0]), sizeof(Tile)* s.tileData.size());
			}

			return true;
		}
	}

	return false;
}

/// Get a tile anywhere in the tilemap, no bound checking
Tile Tilemap::getTile(std::size_t slice_index, std::size_t x, std::size_t y)
{
	return slices[slice_index].tileData[y * width + x];
}

void Tilemap::fill(int32_t w, int32_t h, int32_t sliceCount, uint16_t fillID)
{
	width = w;
	height = h;

	slices.resize(sliceCount);

	Tile fillTile;
	fillTile.id = fillID;

	for (MapSlice& s : slices)
	{
		s.tileData.resize(w*h);
		s.tileData.assign(w*h, fillTile);
	}
}



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
		if(String(it->name()) == "tileset")
		{
			pugi::xml_node inode = it->child("image");

			Tileset t;
			t.mFirstGID = it->attribute("firstgid").as_int(1);
			t.mName =     it->attribute("name").as_string();
			t.mWidth =    inode.attribute("width").as_int();
			t.mHeight =   inode.attribute("height").as_int();
			t.mPath =     inode.attribute("source").as_string();
			t.mSpacing =  it->attribute("spacing").as_int(0);
			t.mTileWidth =it->attribute("tilewidth").as_int();
			t.mTileHeight=it->attribute("tileheight").as_int();
			mTilesets.push_back(t);
		}
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
					obj.mObjectType = Object::PolyLine;
					obj.mName = (*object_it).attribute("name").as_string("");

					obj.mPosition.x = (*object_it).attribute("x").as_float(0);
					obj.mPosition.y = (*object_it).attribute("y").as_float(0);
					
					// Now add all the points
					pugi::xml_node polyline_node = object_it->child("polyline");

					String pointsString = polyline_node.attribute("points").as_string();
					StringList pointList = pointsString.split(' ');
					for(size_t k = 0; k < pointList.size(); ++k)
					{
						StringList vs = pointList[k].split(',');
						vec2 v;
						if(vs.size() == 2)
						{
							v.x = vs[0].toFloat();
							v.y = vs[1].toFloat();
							Log("Pushing point to polyline");
						}
						obj.mPoints.push_back(v);
					}

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

	// Fill the last GID in each tileset
	for(std::size_t i = 0; i < mTilesets.size(); ++i)
	{
		mTilesets[i].computeLastGid();
	}

	return true;
}

/// Get the right UV for a given tile in a given layer
FloatRect Tilemap::getTileUV(const String& layerName, std::size_t tileIndex)
{
	FloatRect rect(0.f, 0.f, 0.f, 0.f);

	Layer* layer = getLayerByName(layerName);
	if(layer && layer->mTileData.size() > tileIndex)
	{
		int gid = layer->mTileData[tileIndex];

		// Find the right UV for this gid
		convertGIDtoUV(gid, rect);

		//Log("gid %d has UV rect %f %f %f %f", gid, rect.left, rect.top, rect.width, rect.height);
	}

	return rect;
}

void Tilemap::convertGIDtoUV(int gid, FloatRect& rect)
{
	if(gid > 0 && mTilesets.size() > 0)
	{
		for(std::size_t i = 0; i < mTilesets.size(); ++i)
		{
			if(mTilesets[i].containsGid(gid))
			{
				//Log("THE GID %d WAS FOUND IN TILESET %d", gid, i);
				rect = mTilesets[i].getNormalizedCoordinates(gid);
			}
		}
	}
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
	for(std::size_t i = 0; i < mLayers.size(); ++i)
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
	for(std::size_t i = 0 ; i < mObjects.size(); ++i)
	{
		if(mObjects[i].mName == name)
		{
			return mObjects[i].mPosition;
		}
	}

	return vec2(0.f, 0.f);
}

std::size_t Tilemap::getTilesetIndexOfGid(int gid)
{
	for(std::size_t i = 0; i < mTilesets.size(); ++i)
	{
		if(mTilesets[i].containsGid(gid))
			return i;
	}

	return 0;
}


/// Check if the 2D coordinate is a valid tile coordinate in the layer
bool Tilemap::Layer::isValidCoordinate2D(vec2i coord)
{
	int maxCoordX = mWidth - 1;
	int maxCoordY = mHeight - 1;

	return (coord.x <= maxCoordX && coord.y <= maxCoordY);
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

/// Get a object from its name
Tilemap::Object* Tilemap::Layer::getObject(const String& name)
{
	for(size_t i = 0; i < mObjects.size(); ++i)
	{
		if(mObjects[i].mName == name)
			return &mObjects[i];
	}
	return NULL;
}

////////////////////////////////////////////////////////////////////////// Tileset

vec2 half_pixel_correction(int x, int y, int tex_width, int tex_height)
{
	vec2 texel_correction(1.f / tex_width, 1.f / tex_height);

	vec2 uv;
	uv.x = (static_cast<float>(x) - texel_correction.x) / tex_width;
	uv.y = (static_cast<float>(y) - texel_correction.y) / tex_height;
	return uv;
}

FloatRect Tilemap::Tileset::getNormalizedCoordinates(int gid)
{
	int tileIndex = gid - mFirstGID; /// will give an index of the wanted tile from 0..tileCount

	//Log("Tile index for gid %d is %d", gid, tileIndex);

	int j = 0;
	int xx = 0;
	int yy = 0; 

	int tilesPerRow = static_cast<float>(mWidth) / (mTileWidth + mSpacing);

	float realWidth = tilesPerRow * mTileWidth;

	// Cycle tiles to find the right one and its coords
	while(j != tileIndex)
	{
		xx += mTileWidth + mSpacing;

		if(xx >= realWidth)
		{
			xx = 0.f;
			yy += mTileHeight + mSpacing;
		}

		j++;
	}

	if(gid == 25)
		Log("Current XX YY %d %d", xx, yy);

	float texel_x = 1.f / mWidth;

	vec2 texel_correction(1.f / mWidth, 1.f / mHeight);
	texel_correction /= 2.f;

	FloatRect rect;
	rect.left = static_cast<float>(xx) / static_cast<float>(mWidth);
	rect.top = static_cast<float>(yy) / static_cast<float>(mHeight);
	rect.width = rect.left + (static_cast<float>(mTileWidth) / mWidth) - texel_x;
	rect.height = rect.top + static_cast<float>(mTileHeight) / mHeight;

	rect.left = float(xx) / mWidth + texel_correction.x; 
	rect.top = float(yy) / mHeight + texel_correction.y;
	rect.width = float(xx + mTileWidth) / mWidth - texel_correction.x;
	rect.height = float(yy + mTileHeight) / mHeight - texel_correction.y;

	return rect;
}

bool Tilemap::Tileset::containsGid(int gid)
{
	if(gid >= mFirstGID && gid < mLastGID)
	{
		return true;
	}
	else
	{
		return false;
	}
}

// Needs testing
void Tilemap::Tileset::computeLastGid()
{
	int tilesInTexture = 0;
	int tilesPerRow = mWidth / mTileWidth;
	int tilesPerColumn = mHeight / mTileHeight;

	tilesPerRow = tilesPerRow - mSpacing * tilesPerRow;
	tilesPerColumn = tilesPerColumn - mSpacing * tilesPerColumn;

	tilesInTexture = tilesPerRow * tilesPerColumn;

	mLastGID = mFirstGID + tilesInTexture;
}


NEPHILIM_NS_END