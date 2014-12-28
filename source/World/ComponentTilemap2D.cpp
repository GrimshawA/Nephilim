#include <Nephilim/World/ComponentTilemap2D.h>
#include <Nephilim/Strings.h>
#include <Nephilim/Math/Vectors.h>
#include <Nephilim/Tilemap.h>
#include <Nephilim/Logger.h>
#include <Nephilim/Path.h>

#include <pugixml/pugixml.hpp>

NEPHILIM_NS_BEGIN
namespace rzr
{

/// Initializes an empty world
ComponentTilemap2D::ComponentTilemap2D()
: mTileSize(1.f, 1.f, 1.f)
, mChunkSize(30.f, 30.f)
{

}

/// Ensure destruction of all dependencies
ComponentTilemap2D::~ComponentTilemap2D()
{

}

/// Check if the tilemap has a layer with this name
bool ComponentTilemap2D::hasLayer(const String& layerName)
{
	for(std::size_t i = 0; i < mLayers.size(); ++i)
	{
		if(mLayers[i].mName == layerName)
			return true;
	}

	return false;
}

/// Check if a given layer has a given object
bool ComponentTilemap2D::hasObject(const String& layerName, const String& objectName)
{
	Tilemap::Layer *tlayer = mTilemapData.getLayerByName(layerName);
	if(tlayer)
	{
		Tilemap::Object* object = tlayer->getObject(objectName);
		return (object != NULL);
	}

	return false;
}

/// Get how many points are there in the object
size_t ComponentTilemap2D::getObjectPointCount(const String& layerName, const String& objectName)
{
	Tilemap::Layer *tlayer = mTilemapData.getLayerByName(layerName);
	if(tlayer)
	{
		Tilemap::Object* object = tlayer->getObject(objectName);
		if(object)
		{
			return object->mPoints.size();
		}
	}

	return 0;
}

/// Get the point i in the given object
vec2 ComponentTilemap2D::getObjectPoint(const String& layerName, const String& objectName, int index)
{
	Tilemap::Layer *tlayer = mTilemapData.getLayerByName(layerName);
	if(tlayer)
	{
		Tilemap::Object* object = tlayer->getObject(objectName);
		if(object)
		{
			return object->mPoints[index];
		}
	}

	return vec2(0.f, 0.f);
}

/// Get the position of the given object
vec2 ComponentTilemap2D::getObjectPosition(const String& layerName, const String& objectName)
{
	Tilemap::Layer *tlayer = mTilemapData.getLayerByName(layerName);
	if(tlayer)
	{
		Tilemap::Object* object = tlayer->getObject(objectName);
		if(object)
		{
			return object->mPosition;
		}
	}

	return vec2(0.f, 0.f);
}

/// Change the tile size
void ComponentTilemap2D::setTileSize(vec3 size)
{
	mTileSize = size;
}

/// The tiles for the main layer are cubes instead of flat squares
void ComponentTilemap2D::useCubes(bool enabled)
{

}

/// Enables the side view type of map mode
void ComponentTilemap2D::setSideView(bool enabled)
{

}

void ComponentTilemap2D::generateCollisionData(const String& layerName, CollisionData& cd)
{
	Tilemap::Layer* tileLayer = mTilemapData.getLayerByName(layerName);
	if(tileLayer)
	{
		CollisionData::Body& body = cd.addBody();

		for(std::size_t i = 0; i < tileLayer->mTileData.size(); ++i)
		{
			if(tileLayer->mTileData[i] > 0)
			{
				// Add tile
				body.addRect(i % tileLayer->mWidth + mTileSize.x / 2.f, i / tileLayer->mWidth + mTileSize.y / 2.f, mTileSize.x, mTileSize.y);
			}
		}
	}
}

bool ComponentTilemap2D::load(const String& filename)
{
	Path path(filename);

	// Load from Tiled format
	if(path.getExtension() == "tmx")
	{
		mTilemapData.loadTMX(filename);
		
		// Total map size
		mLevelSize.x = mTilemapData.mWidth * mTileSize.x;
		mLevelSize.y = mTilemapData.mHeight * mTileSize.y;
		mLevelSizeInTiles.x = mTilemapData.mWidth;
		mLevelSizeInTiles.y = mTilemapData.mHeight;

		Log("=> Loading 2D level with size(%f, %f)", mLevelSize.x, mLevelSize.y);

		// Init the layers
		for(std::size_t i = 0; i < mTilemapData.mLayers.size(); ++i)
		{
			mLayers.push_back(Layer(mTilemapData.mLayers[i]->mName));
		}

		// Init some default chunks
		allocateChunks();

		return true;
	}

	return false;
}

/// Converts the in memory tile data from a single layer to renderizable chunk data
void ComponentTilemap2D::prepareLayer(const String& layerName)
{
	// What we do is to browse the mTilemapData in the right layer and load that data into the chunks
	Tilemap::Layer* td = mTilemapData.getLayerByName(layerName);
	if(td && td->mType == Tilemap::Layer::Tiles)
	{
		//generateCubes(td, layerName);

		generateTiles(td, layerName);
	}
	else
	{
		Log("Failed to prepare layer: %s", layerName.c_str());
	}
}

/// Generates a chunk list for culling out for the entire map
void ComponentTilemap2D::allocateChunks()
{
	int pagesHorizontal = ceilf(mLevelSize.x / (mChunkSize.x * mTileSize.x));
	int pagesVertical = ceilf(mLevelSize.y / (mChunkSize.y * mTileSize.y));

	mNumChunks.x = pagesHorizontal;
	mNumChunks.y = pagesVertical;

	mChunks.resize(pagesHorizontal * pagesVertical);
	for(std::size_t i = 0; i < mChunks.size(); ++i)
	{
		mChunks[i].mLayers.resize(mLayers.size());
		for(std::size_t j = 0; j < mChunks[i].mLayers.size(); ++j)
		{
			mChunks[i].mLayers[j].mName = mLayers[j].mName;
		}
	}

	Log("=> Allocated %d chunks for this map", mChunks.size());
}

Tilemap2DLayer& ComponentTilemap2D::Chunk::getLayer(const String& name)
{
	for(std::size_t i = 0; i < mLayers.size(); ++i)
	{
		if(mLayers[i].mName == name)
			return mLayers[i];
	}
}


};
NEPHILIM_NS_END